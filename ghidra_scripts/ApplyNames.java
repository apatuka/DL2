// Apply function names / plate comments from a TSV file: addr<TAB>name[<TAB>comment]
// Run: analyzeHeadless <proj> DL2 -process DEADLOCK.EXE -noanalysis -scriptPath <dir> -postScript ApplyNames.java <names.tsv>
//@category Export
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.SourceType;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class ApplyNames extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] a = getScriptArgs();
        if (a.length < 1) { printerr("usage: ApplyNames <names.tsv>"); return; }
        FunctionManager fm = currentProgram.getFunctionManager();
        Listing listing = currentProgram.getListing();
        int renamed = 0, commented = 0, missing = 0;
        Set<String> used = new HashSet<>();
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(a[0]), StandardCharsets.UTF_8))) {
            String line;
            while ((line = br.readLine()) != null) {
                if (line.isEmpty() || line.startsWith("#")) continue;
                String[] p = line.split("\t");
                if (p.length < 2) continue;
                Address addr = toAddr(p[0].trim());
                Function f = fm.getFunctionAt(addr);
                if (f == null) { missing++; continue; }
                String name = p[1].trim().replaceAll("[^A-Za-z0-9_:]", "_");
                if (!name.isEmpty()) {
                    String n = name; int k = 2;
                    while (used.contains(n)) n = name + "_" + (k++);
                    used.add(n);
                    if (!f.getName().equals(n)) {
                        try { f.setName(n, SourceType.USER_DEFINED); renamed++; }
                        catch (Exception e) { printerr("rename failed " + p[0] + " -> " + n + ": " + e.getMessage()); }
                    }
                }
                if (p.length >= 3 && !p[2].trim().isEmpty()) {
                    listing.setComment(addr, CodeUnit.PLATE_COMMENT, p[2].trim().replace("\\n", "\n"));
                    commented++;
                }
            }
        }
        println("ApplyNames: renamed=" + renamed + " commented=" + commented + " missing=" + missing);
    }
}
