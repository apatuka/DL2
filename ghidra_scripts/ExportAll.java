// Bulk export of a Ghidra program: functions (decompiled C + metadata), strings, data, imports.
// Run: analyzeHeadless <proj> DL2 -process DEADLOCK.EXE -noanalysis -scriptPath <dir> -postScript ExportAll.java <outdir>
//@category Export
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import ghidra.program.model.data.*;
import java.io.*;
import java.util.*;

public class ExportAll extends GhidraScript {
    static String esc(String s) {
        if (s == null) return "";
        StringBuilder b = new StringBuilder();
        for (char c : s.toCharArray()) {
            if (c == '"') b.append("\\\"");
            else if (c == '\\') b.append("\\\\");
            else if (c == '\n') b.append("\\n");
            else if (c == '\r') b.append("\\r");
            else if (c == '\t') b.append("\\t");
            else if (c < 0x20) b.append(String.format("\\x%02x", (int) c));
            else b.append(c);
        }
        return b.toString();
    }

    static PrintWriter open(File f) throws IOException {
        return new PrintWriter(new OutputStreamWriter(new FileOutputStream(f), "UTF-8"));
    }

    @Override
    public void run() throws Exception {
        String[] a = getScriptArgs();
        File out = new File(a.length > 0 ? a[0] : "C:/Games/DL2/re");
        File dec = new File(out, "decomp");
        dec.mkdirs();
        DecompInterface di = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        di.setOptions(opts);
        di.toggleCCode(true);
        di.toggleSyntaxTree(false);
        di.setSimplificationStyle("decompile");
        di.openProgram(currentProgram);
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();
        Listing listing = currentProgram.getListing();
        PrintWriter idx = open(new File(out, "functions.jsonl"));
        PrintWriter all = open(new File(out, "decompiled_all.c"));
        int n = 0, fail = 0;
        for (Function f : fm.getFunctions(true)) {
            if (monitor.isCancelled()) break;
            n++;
            String name = f.getName();
            Address ea = f.getEntryPoint();
            long size = f.getBody().getNumAddresses();
            StringBuilder callers = new StringBuilder(), callees = new StringBuilder();
            for (Function c : f.getCallingFunctions(monitor)) { if (callers.length() > 0) callers.append(","); callers.append(c.getName()); }
            for (Function c : f.getCalledFunctions(monitor)) { if (callees.length() > 0) callees.append(","); callees.append(c.getName()); }
            StringBuilder strs = new StringBuilder();
            Set<String> seen = new HashSet<>();
            AddressIterator ai = rm.getReferenceSourceIterator(f.getBody(), true);
            while (ai.hasNext()) {
                Address src = ai.next();
                for (Reference r : rm.getReferencesFrom(src)) {
                    Data d = listing.getDataAt(r.getToAddress());
                    if (d != null && d.hasStringValue()) {
                        String v = d.getDefaultValueRepresentation();
                        if (seen.add(v)) { if (strs.length() > 0) strs.append("|"); strs.append(esc(v)); }
                    }
                }
            }
            String code; boolean ok = true;
            try {
                DecompileResults res = di.decompileFunction(f, 120, monitor);
                if (res != null && res.decompileCompleted() && res.getDecompiledFunction() != null) code = res.getDecompiledFunction().getC();
                else { code = "/* DECOMPILE FAILED: " + (res != null ? res.getErrorMessage() : "null") + " */\n"; ok = false; fail++; }
            } catch (Exception e) { code = "/* EXC: " + e + " */\n"; ok = false; fail++; }
            String fn = String.format("%s_%s.c", ea.toString(), name.replaceAll("[^A-Za-z0-9_@$]", "_"));
            try (PrintWriter pw = open(new File(dec, fn))) {
                pw.println("// " + name + " @ " + ea + " size=" + size + " sig=" + f.getPrototypeString(false, false) + " cc=" + f.getCallingConventionName());
                pw.println("// callers: " + callers);
                pw.println("// callees: " + callees);
                if (strs.length() > 0) pw.println("// strings: " + strs);
                pw.print(code);
            }
            all.println("// ===== " + name + " @ " + ea + " size=" + size);
            all.print(code);
            all.println();
            idx.println("{\"addr\":\"" + ea + "\",\"name\":\"" + esc(name) + "\",\"size\":" + size + ",\"sig\":\"" + esc(f.getPrototypeString(false, false)) + "\",\"cc\":\"" + f.getCallingConventionName() + "\",\"ok\":" + ok + ",\"callers\":\"" + esc(callers.toString()) + "\",\"callees\":\"" + esc(callees.toString()) + "\",\"strings\":\"" + strs + "\"}");
            if (n % 250 == 0) println("exported " + n + " functions (" + fail + " failed)");
        }
        idx.close();
        all.close();
        try (PrintWriter pw = open(new File(out, "strings.tsv"))) {
            DataIterator dit = listing.getDefinedData(true);
            while (dit.hasNext()) {
                Data d = dit.next();
                if (!d.hasStringValue()) continue;
                StringBuilder refs = new StringBuilder();
                for (Reference r : rm.getReferencesTo(d.getAddress())) {
                    Function ff = fm.getFunctionContaining(r.getFromAddress());
                    refs.append(ff != null ? ff.getName() : r.getFromAddress().toString()).append(",");
                }
                pw.println(d.getAddress() + "\t" + d.getDataType().getName() + "\t" + esc(d.getDefaultValueRepresentation()) + "\t" + refs);
            }
        }
        try (PrintWriter pw = open(new File(out, "data.tsv"))) {
            DataIterator dit = listing.getDefinedData(true);
            while (dit.hasNext()) {
                Data d = dit.next();
                if (d.hasStringValue()) continue;
                int nrefs = rm.getReferenceCountTo(d.getAddress());
                pw.println(d.getAddress() + "\t" + d.getDataType().getName() + "\t" + d.getLength() + "\t" + d.getLabel() + "\t" + nrefs);
            }
        }
        try (PrintWriter pw = open(new File(out, "symbols.tsv"))) {
            SymbolIterator si = currentProgram.getSymbolTable().getAllSymbols(true);
            while (si.hasNext()) {
                Symbol s = si.next();
                pw.println(s.getAddress() + "\t" + s.getSymbolType() + "\t" + s.getName() + "\t" + s.getSource() + "\t" + s.getReferenceCount());
            }
        }
        println("DONE functions=" + n + " failed=" + fail);
        di.dispose();
    }
}
