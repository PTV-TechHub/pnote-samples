# synapse-city — Mã mẫu Synapse City (AI ROC 2026)

Mã mẫu mà các bài học Synapse City trên learn.pythaverse.space trỏ tới (link `git.pythaverse.space/ptvairoc/Synapsecity_<cấp>/…`).
Có sẵn ở đây để học sinh và giáo viên **không cần quyền vào kho PGit** (xem Pythaverse2026#640) và không phải tải lên PNote.

| Thư mục | Khoá | Loại tệp | Mở bằng |
|---|---|---|---|
| `primary/` (5 tệp) | 1437 `airoc2026.primary.en` (Robotics & AI Explorer) | `.bduino` (khối lệnh Blockly) | Trình soạn khối Leanbot (ide.pythaverse.space/lbeditor/) hoặc Virtual Leanbot chế độ khối: tải tệp xuống rồi mở |
| `secondary/` (22 tệp) | 1441 `airoc2026.secondary.en` (Smart Robotics & Data AI) | `.ino` (Arduino C++), `dtree.py` | `.ino`: Leanbot IDE (ide.pythaverse.space), sao chép nội dung vào; `dtree.py`: PNote |
| `highschool/` (21 tệp) | 1489 `airoc2026.highschool.en` (Advanced AI & Multi-Agent Systems) | `.ino` (Arduino C++) | Leanbot IDE |

Tên tệp giữ như trên PGit; tệp nào trên PGit không có phần mở rộng thì được thêm `.ino` / `.bduino` / `.py` theo nội dung
(ví dụ `Analyst` → `Analyst.ino`). Trong PNote bạn mở mọi tệp để đọc (chuột phải → Open With → Editor).

## Tệp nào dùng ở bài nào

Theo link trong các hoạt động H5P của khoá (kiểm tra ngày 2026-10-23):

| Tệp | 1437 (primary) | 1441 (secondary) | 1489 (highschool) |
|---|---|---|---|
| `FollowLine_EN.bduino` / `Followline.ino` | Bài 4 *Follow the Smart road* | Bài 4 *The Smart Logistics Network* | Bài 4 *The Smart Logistics Network* |
| `Lesson5_1.ino`, `Lesson5_2.ino` | | Bài 5 *The Sensor's Vision* | Bài 5 *The Sensor's Vision* |
| `Lesson5_3.ino` | | Bài 5 | |
| `M2L1.ino` | | (bài 6 trỏ tới một kho khác; tệp ở đây cùng tên) | Bài 6 *The Physics of Robotic Vision* |
| `sampling.ino` (đo màu, in JSON ra Serial) | | Bài 10 *From Rules to Data* | Bài 5, 8, 11 |
| `Advance Color.ino` | | Bài 9 *Advanced Custom Color Detection* | |
| `templae.ino` (khung để dán luật cây quyết định) | | | Bài 10 *Advanced Custom Color Detection* |
| `dtree.py` (huấn luyện cây quyết định) | | Bài 12 *Training the Brain — Decision Trees* | |
| Dữ liệu `Indoor with Normal Lighting 1–3.json` | | Bài 11 *Big Data — Collection & Preparation*: có trong **`../leanbot-basic/data/`** (giống hệt) | |
| `Ultrasonic Sensor Sending Data to IOT Dashboard.ino` | | Bài 18 *Mastering the IoT Dashboard* | Bài 19 *Mastering the IoT Dashboard* |
| `IoT Dashboard Attribute to LEANBOT OLED Display.ino` | | Bài 19 *Programming Sensory Intelligence* | Bài 20 *Sensory Intelligence* |
| `LEANBOT Data Communication Using IoT Dashboard_LEANBOT A.ino` / `_LEANBOT B.ino`, `LEANBOT Detecting Colored Objects.ino` | | Bài 20 *Collaborative Retrieval* | Bài 21 *Multi-Agent Collaboration* |
| `Containment.bduino` / `Containment.ino` (nhiệm vụ 1) | Bài 13, 14 | | |
| `Neutralizer.bduino` / `Neutralizer.ino` (nhiệm vụ 2) | | Bài 22, 23 | Bài 23 |
| `Analyst.bduino` / `Analyst.ino` (nhiệm vụ 3) | Bài 15 | | Bài 24 |
| `Fullmision.bduino` / `Fullmision_LeanbotA.ino` + `Fullmission_LeanbotB.ino` (nhiệm vụ tổng hợp, 2 robot qua IoT Dashboard) | Bài 16 | Bài 24 | Bài 25 |

Các tệp còn lại có trong kho nhưng không bài nào trỏ tới: `3 Mission_ Not Iot.ino` (3 nhiệm vụ liền nhau, không dùng IoT),
`M2_L2.ino`, `MsDev.ino` (khung trống), `Containment.ino` (secondary, highschool), `Analyst.ino` (secondary), `Neutralizer.bduino` (primary; bài 14 của khoá 1437 trỏ tới `Containment.bduino`).

## Wi-Fi trong các tệp IoT

Các tệp IoT (`…IoT Dashboard…`, `Fullmision_LeanbotA.ino`, `Fullmission_LeanbotB.ino`) có hai dòng:

```cpp
#define  WIFI_SSID      F("YOUR_WIFI_SSID")
#define  WIFI_PASSWORD  F("YOUR_WIFI_PASSWORD")
```

Thay bằng tên và mật khẩu Wi-Fi **của lớp bạn** trước khi nạp vào Leanbot. Không đưa mật khẩu thật lên PGit hay vào bộ mẫu này.

## Nguồn

| Thư mục | Kho PGit | Commit |
|---|---|---|
| `primary/` | `ptvairoc/Synapsecity_Primary` | `dab7213c` (master) |
| `secondary/` | `ptvairoc/Synapsecity_Secondary` | `c0722a17` = `b84e1a07` (master ngày 2026-10-23) + commit thay Wi-Fi bằng chỗ trống |
| `highschool/` | `ptvairoc/Synapsecity_HighSchool` | `2f639804` = `ac58d2bb` (master ngày 2026-10-23) + commit thay Wi-Fi bằng chỗ trống |

Nội dung giữ nguyên, trừ hai điểm: thêm phần mở rộng tệp, và thông tin Wi-Fi mẫu được thay bằng `YOUR_WIFI_SSID` /
`YOUR_WIFI_PASSWORD` (giống commit chuẩn bị cho chính các kho PGit, Pythaverse2026#640). Bản quyền: Pythaverse / AI ROC 2026.
