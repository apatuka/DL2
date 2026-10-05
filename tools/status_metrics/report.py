import json
from pathlib import Path


def render(report, destination):
    template = Path(__file__).with_name("dashboard.html").read_text(encoding="utf-8")
    # Data never becomes markup, even if a test name/source contains </script>.
    payload = json.dumps(report, ensure_ascii=True).replace("<", "\\u003c").replace(">", "\\u003e").replace("&", "\\u0026")
    Path(destination).write_text(template.replace("__STATUS_DATA__", payload), encoding="utf-8")
