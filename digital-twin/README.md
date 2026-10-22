# digital-twin — Chương trình mẫu Virtual Leanbot / Digital Twin

Các chương trình mẫu của Virtual Leanbot (digitaltwin.pythaverse.space) và hai bảng số liệu so sánh robot thật với robot ảo.
Có **ba loại**, chạy ở ba nơi khác nhau. Xem cột "Chạy ở đâu" trước khi mở.

## `pnote/`: chạy trong PNote (thư viện `pyLeanbot` của PNote)

Dùng `from pyLeanbot import *` và `LbMission.beginDigitalTwin(<mã bản đồ>)`: PNote nối với robot ảo qua MQTT, in
"Please go to … to START", rồi bạn bấm **START** trên trang Digital Twin (digitaltwin.pythaverse.space/experience) để robot ảo chạy.

| Tệp | Làm gì |
|---|---|
| `pnote/Demo.py` | Bản đồ `SynapseCity.01`: mở kẹp, chạy thẳng 1,2 s, dừng, đóng kẹp. Mẫu ngắn nhất, cùng kiểu với mã Blockly-Python sinh ra ở các bài mô phỏng (khoá 1437 bài 10–12, 1441 bài 15–16, 1489 bài 16–17) |
| `pnote/msNumberGrid.py` | Bản đồ `msNumberGrid`: 13 vòng "chạy thẳng 1 s, quay 0,5 s" |

Hai tệp này là bản cho PNote của `virtualleanbot/Demo.py` và `virtualleanbot/msNumberGrid.py`: chỉ bỏ tham số
`speedUp=...`, vì `pyLeanbot` trong PNote chỉ nhận mã bản đồ (`beginDigitalTwin(missionId)`; bản gốc báo `TypeError`).

Chạy: dán nội dung vào một ô notebook rồi chạy (đọc trực tiếp từ `samples/` được, không cần sao chép), hoặc trong Terminal
`python ~/work/samples/digital-twin/pnote/Demo.py`. Mỗi lần sửa mã, chạy lại rồi bấm START lại trên trang Digital Twin.

## `virtualleanbot/`: chạy trong Virtual Leanbot (digitaltwin.pythaverse.space, chế độ Python)

Bản gốc từ thư mục `Demo/` của Virtual Leanbot. Chúng dùng các hàm chỉ có trong trình chạy Python của Virtual Leanbot
(`pyLeanbot2`, `SynapseCity`, `LbIoT`, `speedUp=`, Serial của trang Simulator), **không chạy được trong PNote**: mở tệp,
sao chép nội dung và dán vào Virtual Leanbot.

| Tệp | Nội dung |
|---|---|
| `virtualleanbot/Demo.py`, `virtualleanbot/msNumberGrid.py` | Bản gốc của hai mẫu trong `pnote/` (có `speedUp`) |
| `virtualleanbot/LeanbotIoT.py` | Ghi rồi đọc thuộc tính `notes` của một asset trên IoT Dashboard (OpenRemote) bằng `LbIoT`; asset demo dùng chung, đổi `ASSET_ID` sang asset của bạn |
| `virtualleanbot/SerialEcho.py` | Kiểu Arduino (`setup()`/`loop()`): nhắc lại mọi dòng gõ vào Serial Monitor của trang Simulator |
| `virtualleanbot/FollowLine.py` | Dò line quanh viền bản đồ Synapse City rồi về chỗ cũ |
| `virtualleanbot/Containment.py` | Nhiệm vụ 1 *Containment*: đẩy khối xanh lá ở B1 vào vùng chứa B |
| `virtualleanbot/Neutralize.py` | Nhiệm vụ 2 *Neutralizer*: lấy khối trung hoà ở S3, rồi xử lý khối ô nhiễm xanh dương ở E2 |
| `virtualleanbot/Analysis.py` | Nhiệm vụ 3 *Analysis*: lấy mẫu khối đỏ ở F4 mang về phân tích |
| `virtualleanbot/Combined.py` | Gộp cả ba nhiệm vụ trong một lượt (trung hoà E2, chứa B1, thu khối đỏ F4) |
| `virtualleanbot/ColorDemo.py` | Đọc màu một khối ngẫu nhiên ở E4 (không chạm khối), rồi thu gom hoặc trung hoà tuỳ màu |
| `virtualleanbot/RandomLayout.py` | Đặt khối ngẫu nhiên theo cấp (EXPLORER 4, CREATOR 5, INNOVATOR 6, MASTER 7 khối) và in bố cục để dùng lại |
| `virtualleanbot/TestCollision.py` | Kiểm tra `testCollision()` khi khối chạm robot (dành cho giáo viên / kỹ thuật) |

## `blockly/`: tệp khối lệnh (`.bduino`, `.xml`)

Mở trong trình soạn khối của Leanbot (ide.pythaverse.space → Blockly) hoặc Virtual Leanbot (chế độ khối): tải tệp xuống
máy (chuột phải → Download) rồi dùng nút mở tệp của trình soạn.

| Tệp | Nội dung |
|---|---|
| `Demo.bduino`, `FollowLine.bduino`, `LeanbotIoT.bduino` | Bản khối lệnh của các mẫu cùng tên ở trên |
| `Containment.bduino`, `Neutralize.bduino`, `Analysis.bduino`, `ColorDemo.bduino` | Bản khối lệnh của các nhiệm vụ Synapse City |
| `Variables.bduino` | Mẫu kiểm tra biến (dành cho kỹ thuật) |
| `Mission_11.1.xml` | Bài mẫu "LeanbotCourseDemo / Mission 11.1" của trình soạn Blockly-Python |

## `data/`: số liệu đo (CSV, đọc bằng pandas)

| Tệp | Nội dung |
|---|---|
| `data/leanbot-physical-vs-virtual.csv` | Cùng một lệnh chạy, so sánh robot thật với robot ảo: tick, vị trí và độ lệch, ở 8 tốc độ (250–2000). Mỗi tốc độ bắt đầu bằng một dòng tiêu đề `speed <n>` |
| `data/leanbot-3-units.csv` | Cùng lệnh chạy trên 3 robot thật: tick, vị trí (mm) và độ lệch giữa 3 robot (`pos spread`) |

```python
import pandas as pd
df = pd.read_csv("samples/digital-twin/data/leanbot-3-units.csv")
df.groupby("speed")["pos spread"].max()

# leanbot-physical-vs-virtual.csv: tách theo dòng "speed <n>"
v = pd.read_csv("samples/digital-twin/data/leanbot-physical-vs-virtual.csv")
v["speed"] = v["i"].where(v["i"].str.startswith("speed")).ffill()
v = v[~v["i"].str.startswith("speed")].astype({"pos difference": int})
v.groupby("speed")["pos difference"].agg(["min", "max"])
```

## Nguồn

GitHub `PTV-TechHub/digitaltwins-service`, nhánh `digital_twins_pythaverse_v1.1-prod`, commit `ba552ed9` (lấy ngày
2026-10-23): `digital-twins/client/public/Demo/` (các tệp `.py`, `.bduino`; giống hệt bản đang phục vụ tại
digitaltwin.pythaverse.space/Demo/), `digital-twins/client/public/LB-blockly-python/examples/LeanbotCourseDemo/Mission_11.1.xml`,
`digital-twins/docs/leanbot-physical-vs-virtual.csv`, `digital-twins/docs/leanbot-3-units.csv`.

Thay đổi duy nhất: trong `leanbot-3-units.csv`, tên cột theo số hiệu của 3 robot thử nghiệm được đổi thành `robot1`,
`robot2`, `robot3` (số liệu giữ nguyên). Các tệp `.py` được xếp lại thư mục theo nơi chạy (gốc: `Demo/`, `Demo/SynapseCity/`,
`Demo/Test/`), và `pnote/Demo.py`, `pnote/msNumberGrid.py` là bản đã bỏ `speedUp` (ghi chú ở dòng 2 của mỗi tệp).
