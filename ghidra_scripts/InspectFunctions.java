// Export focused pseudocode and assembly without replacing historical exports.
// Arguments: fresh-output-directory address [address ...]
//@category Export
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;

public class InspectFunctions extends GhidraScript {
    @Override public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) throw new IllegalArgumentException("output-directory address...");
        Path output = Paths.get(args[0]);
        Files.createDirectories(output);
        DecompInterface decompiler = new DecompInterface();
        try {
            decompiler.openProgram(currentProgram);
            for (int n = 1; n < args.length; ++n) {
                Address address = toAddr(args[n]);
                Function function = currentProgram.getFunctionManager().getFunctionAt(address);
                if (function == null) throw new IllegalArgumentException("No function at " + address);
                StringBuilder text = new StringBuilder();
                text.append("// Program: ").append(currentProgram.getName()).append('\n');
                text.append("// Language: ").append(currentProgram.getLanguageID()).append('\n');
                text.append("// Compiler: ").append(currentProgram.getCompilerSpec().getCompilerSpecID()).append('\n');
                text.append("// Function: ").append(function.getEntryPoint()).append(' ').append(function.getName()).append('\n');
                DecompileResults result = decompiler.decompileFunction(function, 120, monitor);
                if (result.decompileCompleted() && result.getDecompiledFunction() != null)
                    text.append(result.getDecompiledFunction().getC());
                else text.append("// DECOMPILATION FAILED: ").append(result.getErrorMessage()).append('\n');
                text.append("\n/* ASSEMBLY\n");
                for (Instruction instruction : currentProgram.getListing().getInstructions(function.getBody(), true))
                    text.append(instruction.getAddress()).append("  ").append(instruction).append('\n');
                text.append("*/\n");
                Files.writeString(output.resolve(address.toString() + ".txt"), text,
                    StandardCharsets.UTF_8, StandardOpenOption.CREATE_NEW);
                println("Exported " + address + " " + function.getName());
            }
        } finally { decompiler.dispose(); }
    }
}
