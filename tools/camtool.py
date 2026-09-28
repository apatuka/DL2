#!/usr/bin/env python3
"""camtool.py - inspect / extract Cyberlore CAM packages and HDX/HDD archives (Deadlock II).

CAM ("CYLBPC  ") layout (all little-endian):
    char   magic[8]      "CYLBPC  "
    u16    ver_major, ver_minor   (1, 1)
    u32    num_sections
    u32    directory_size          (bytes of all section directories that follow the type table)
    struct { char tag[4]; u32 section_offset; } types[num_sections]
    -- per section (at section_offset) --
    u32    count
    u32    flags                    (1 = entries are unnamed / indexed)
    struct { char name[20]; u32 offset; u32 size; } entries[count]   (offset is absolute in file)

HDX index: u32 count; struct { char name[8]; u32 offset; } [count]
HDD data : at offset -> u32 length, then payload[length]
"""
import os, struct, sys, io

def read_cam(path):
    with open(path, "rb") as f:
        d = f.read()
    if d[:8] != b"CYLBPC  ":
        raise ValueError("not a CAM file")
    vmaj, vmin, nsec, dirsize = struct.unpack_from("<HHII", d, 8)
    secs = {}
    for i in range(nsec):
        tag = d[20 + i * 8:24 + i * 8].decode("ascii")
        off = struct.unpack_from("<I", d, 24 + i * 8)[0]
        cnt, flags = struct.unpack_from("<II", d, off)
        ents = []
        for k in range(cnt):
            p = off + 8 + k * 28
            raw = d[p:p + 20]
            eo, es = struct.unpack_from("<II", d, p + 20)
            if flags & 1:
                name = str(struct.unpack_from("<I", raw, 0)[0])
            else:
                name = raw.split(b"\0", 1)[0].decode("latin-1")
            ents.append({"name": name, "raw": raw, "offset": eo, "size": es})
        secs[tag] = {"flags": flags, "entries": ents}
    return d, secs

def read_hdx(base):
    with open(base + ".HDX", "rb") as f:
        idx = f.read()
    n = struct.unpack_from("<I", idx, 0)[0]
    ents = []
    for i in range(n):
        name, off = struct.unpack_from("<8sI", idx, 4 + i * 12)
        ents.append((name.rstrip(b"\0").decode("latin-1"), off))
    return ents

def hdd_read(base, off):
    with open(base + ".HDD", "rb") as f:
        f.seek(off)
        n = struct.unpack("<I", f.read(4))[0]
        return f.read(n)

def palette_from_palt(blob):
    """PALT entry: 12-byte header then 255 RGBx quads, index 255 implicit white."""
    pal = [(blob[12 + i * 4], blob[13 + i * 4], blob[14 + i * 4]) for i in range(255)]
    pal.append((255, 255, 255))
    return pal

def decode_iff_pbm(blob):
    """PICT type 2: u32 type(2) then IFF 'FORM' 'PBM ' (Deluxe Paint 8-bit). Returns (w,h,pal,pixels)."""
    p = 4
    assert blob[p:p + 4] == b"FORM"
    p += 8
    assert blob[p:p + 4] == b"PBM ", blob[p:p+4]
    p += 4
    w = h = 0; pal = None; pix = None; compr = 0
    while p + 8 <= len(blob):
        ck = blob[p:p + 4]; ln = struct.unpack(">I", blob[p + 4:p + 8])[0]; body = blob[p + 8:p + 8 + ln]
        if ck == b"BMHD":
            w, h, x, y, nplanes, mask, compr = struct.unpack(">HHhhBBB", body[:11])
        elif ck == b"CMAP":
            pal = [(body[i], body[i + 1], body[i + 2]) for i in range(0, len(body), 3)]
        elif ck == b"BODY":
            if compr == 1:  # ByteRun1
                out = bytearray(); i = 0
                while i < len(body) and len(out) < w * h:
                    n = body[i]; i += 1
                    if n < 128:
                        out += body[i:i + n + 1]; i += n + 1
                    elif n > 128:
                        out += bytes([body[i]]) * (257 - n); i += 1
                pix = bytes(out)
            else:
                pix = body
        p += 8 + ln + (ln & 1)
    return w, h, pal, pix

def main():
    if len(sys.argv) < 3:
        print(__doc__); print("usage: camtool.py list|extract <file.cam> [outdir]\n       camtool.py hdd <BASE> [outdir]"); return
    cmd, path = sys.argv[1], sys.argv[2]
    outdir = sys.argv[3] if len(sys.argv) > 3 else None
    if cmd in ("list", "extract"):
        d, secs = read_cam(path)
        for tag, s in secs.items():
            print(f"[{tag}] count={len(s['entries'])} flags={s['flags']}")
            for e in s["entries"]:
                if cmd == "list":
                    print(f"   {e['name']:<20} off={e['offset']:>10} size={e['size']:>9} head={d[e['offset']:e['offset']+8].hex(' ')}")
                else:
                    od = os.path.join(outdir or os.path.splitext(path)[0] + "_out", tag); os.makedirs(od, exist_ok=True)
                    blob = d[e["offset"]:e["offset"] + e["size"]]
                    ext = ".wav" if blob[:4] == b"RIFF" else ".smk" if blob[4:8] == b"SMK2" else ".bin"
                    with open(os.path.join(od, e["name"].replace("/", "_") + ext), "wb") as f:
                        f.write(blob[4:] if ext == ".smk" else blob)
    elif cmd == "hdd":
        ents = read_hdx(path)
        for name, off in ents:
            blob = hdd_read(path, off)
            print(f"   {name:<9} off={off:>10} size={len(blob):>9} head={blob[:8].hex(' ')}")
            if outdir:
                os.makedirs(outdir, exist_ok=True)
                ext = ".bmp" if blob[:2] == b"BM" else ".txt" if blob[:1].isalpha() or blob[:1] in b"\r\n" else ".bin"
                with open(os.path.join(outdir, name + ext), "wb") as f:
                    f.write(blob)

if __name__ == "__main__":
    main()
