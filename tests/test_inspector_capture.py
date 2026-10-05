"""Check real inspector BMP output and exclusive creation with the installed SDL runtime."""
from pathlib import Path
import struct
import subprocess
import sys
import tempfile


def main():
    executable, data_dir, build_dir = map(Path, sys.argv[1:])
    with tempfile.TemporaryDirectory(prefix="inspector-capture-", dir=build_dir) as directory:
        destination = Path(directory) / "capture.bmp"

        def capture(path):
            return subprocess.run(
                [str(executable), str(data_dir), "--smoke-frames", "3", "--screenshot", str(path)],
                cwd=executable.parent, capture_output=True, timeout=20,
            ).returncode

        if capture(destination) != 0:
            raise RuntimeError("Inspector screenshot failed")
        image = destination.read_bytes()
        if image[:2] != b"BM" or len(image) < 54:
            raise RuntimeError("Inspector did not produce a BMP")
        if struct.unpack_from("<I", image, 2)[0] != len(image):
            raise RuntimeError("BMP is truncated or has unexpected trailing bytes")
        if struct.unpack_from("<ii", image, 18) != (640, 480):
            raise RuntimeError("Unexpected inspector image dimensions")
        pixel_offset = struct.unpack_from("<I", image, 10)[0]
        if pixel_offset >= len(image) or len(set(image[pixel_offset:])) < 4:
            raise RuntimeError("Inspector image has no rendered content")
        if capture(destination) == 0 or destination.read_bytes() != image:
            raise RuntimeError("Screenshot overwrote an existing file or reported success")
        if capture(Path(directory) / "missing" / "capture.bmp") == 0:
            raise RuntimeError("Screenshot accepted a missing destination directory")
    print("Inspector capture: valid 640x480 BMP; existing files preserved; invalid path rejected.")


if __name__ == "__main__":
    main()
