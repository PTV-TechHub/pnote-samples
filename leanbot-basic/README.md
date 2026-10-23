# leanbot-basic — Phân loại màu vật thể bằng AI (Leanbot + cảm biến màu APDS-9960)

Bộ dữ liệu và mã mẫu của bài **"Object Color Classification with AI Model"**: Leanbot đo màu các khối (đỏ, vàng, xanh lá,
xanh dương, tím) bằng cảm biến APDS-9960, ghi số đo ra JSON; trong PNote ta dùng các tệp JSON đó để huấn luyện một cây
quyết định (decision tree) rồi nạp luật vào Leanbot.

## Các tệp

| Tệp | Là gì | Dùng ở đâu |
|---|---|---|
| `data/Indoor with Normal Lighting 1.json` | 100 mẫu (20 mỗi màu: YELLOW, GREEN, BLUE, PURPLE, RED), đo trong phòng, ánh sáng thường. Mỗi mẫu: `objColor` (nhãn), `objRed`, `objGreen`, `objBlue` (số đo cảm biến) | Khoá 1441 bài 11 *Big Data — Collection & Preparation* (link trong bài); hướng dẫn PGit *Object Color Classification* |
| `data/Indoor with Normal Lighting 2.json` | 100 mẫu, lần đo thứ 2 | như trên |
| `data/Indoor with Normal Lighting 3.json` | 100 mẫu, lần đo thứ 3 | như trên |
| `code/dtree.py` | Đọc mọi `*.json` trong **thư mục hiện tại**, bỏ mẫu âm, chia 80/20 theo màu, huấn luyện `DecisionTreeClassifier(max_depth=5)`, in luật, vẽ cây (lưu `dtree.jpg`) và ma trận nhầm lẫn | Khoá 1441 bài 12 *Training the Brain — Decision Trees* (link `Synapsecity_Secondary/dtree`, cùng nội dung) |
| `code/samplingColor.ino` | Mã Arduino cho Leanbot: đo màu và in mẫu JSON ra Serial Monitor (để tự thu dữ liệu) | Mở bằng Leanbot IDE (ide.pythaverse.space). Bản gần giống `sampling` của Synapse City (khoá 1441 bài 10; 1489 bài 5, 8, 11) |
| `code/template.ino` | Khung chương trình để dán luật cây quyết định vào | Hướng dẫn PGit; bản gần giống `templae` (khoá 1489 bài 10) |
| `code/classifiyColor.ino` | Chương trình hoàn chỉnh: phân loại màu trên Leanbot bằng luật đã huấn luyện | Hướng dẫn PGit |
| `bat-dau-voi-du-lieu-mau.ipynb` | Notebook ngắn: đọc 3 tệp JSON, đếm mẫu theo màu, vẽ biểu đồ, huấn luyện thử cây quyết định (không ghi tệp nào) | Mở ngay trong `samples/` |

Ba tệp JSON giống hệt bản trong `ptvairoc/Synapsecity_Secondary` mà khoá 1441 bài 11 trỏ tới, nên thư mục
`synapse-city/` không chép lại.

## Cách dùng trong PNote

Đọc trực tiếp (notebook của bạn ở thư mục gốc):

```python
import glob
import pandas as pd
files = sorted(glob.glob("samples/leanbot-basic/data/*.json"))
df = pd.concat([pd.read_json(f) for f in files], ignore_index=True)
df.head()
```

Chạy `dtree.py` (nó đọc `*.json` ở thư mục hiện tại và **ghi** `dtree.jpg`, nên phải chạy trong thư mục của bạn):

```python
# 1. sao chép một lần (hoặc chạy samples/sao-chep-vao-thu-muc-cua-toi.ipynb)
!cp -r --update=none ~/work/samples/leanbot-basic ~/work/
# 2. chạy trong thư mục dữ liệu
%cd ~/work/leanbot-basic/data
%run ../code/dtree.py
```

Thêm dữ liệu của chính bạn: tải tệp JSON bạn đo được (Serial Monitor → lưu `.json`) vào `~/work/leanbot-basic/data/`,
rồi chạy lại. Dữ liệu tự đo **không** đưa vào bộ mẫu này.

## Nguồn

PGit `quang.dinh/Leanbot_Programming_Guide`, thư mục *Object Color Classification with AI Model* (`Data/`, `Code/`),
commit `c2ed6ed4` trên `master`, lấy ngày 2026-10-23. Nội dung giữ nguyên; tác giả: nhóm Leanbot / Pythaverse.
