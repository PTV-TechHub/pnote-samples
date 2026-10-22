# Dữ liệu mẫu PNote (pnote-samples)

Bộ tệp mẫu có sẵn trong mọi máy chủ PNote (https://note.pythaverse.space), để học sinh và giáo viên **không phải tự tải lên**
dữ liệu và mã mẫu của các bài học Leanbot, Digital Twin và Synapse City.

Trong PNote, thư mục này hiện ở **`samples/`** (đường dẫn đầy đủ `/home/jovyan/work/samples`). Thư mục **chỉ đọc**: bạn mở,
chạy và đọc dữ liệu được, nhưng không sửa hay lưu đè được. Muốn sửa, hãy sao chép sang thư mục của mình (xem bên dưới).

| Thư mục | Nội dung | Số tệp |
|---|---|---|
| [`leanbot-basic/`](leanbot-basic/README.md) | Bộ dữ liệu màu "Indoor with Normal Lighting 1–3" (JSON), mã huấn luyện cây quyết định `dtree.py`, mã Arduino đo màu, notebook bắt đầu | 9 |
| [`digital-twin/`](digital-twin/README.md) | Chương trình mẫu cho Virtual Leanbot / Digital Twin: chạy trong PNote (`pyLeanbot`), trong trình chạy Python của Virtual Leanbot (`pyLeanbot2`), tệp Blockly `.bduino`, 2 bảng số liệu đo | 24 |
| [`synapse-city/`](synapse-city/README.md) | Mã mẫu Synapse City (AI ROC 2026) theo cấp: tiểu học (Blockly), THCS và THPT (Arduino `.ino`, `dtree.py`) | 49 |

Tổng: 84 tệp (kể cả các README và notebook), khoảng 0,75 MB. Số tệp tính cả README của từng thư mục.

## Dùng trong PNote

**Đọc dữ liệu trực tiếp (không cần sao chép).** Notebook nằm ở thư mục gốc của bạn:

```python
import glob
import pandas as pd

files = sorted(glob.glob("samples/leanbot-basic/data/*.json"))
df = pd.concat([pd.read_json(f) for f in files], ignore_index=True)
print(len(df), "mẫu"); print(df["objColor"].value_counts())
```

Ở bất kỳ thư mục nào, dùng đường dẫn đầy đủ: `/home/jovyan/work/samples/leanbot-basic/data/...`.

**Sao chép sang thư mục của mình (để sửa).** Ba cách:

1. Mở `samples/sao-chep-vao-thu-muc-cua-toi.ipynb` và bấm **Run → Run All Cells**. Các tệp được chép sang
   `mau-cua-toi/` ở thư mục gốc của bạn; tệp bạn đã có sẵn thì **không bị ghi đè**.
2. Trong thanh tệp bên trái: chuột phải vào tệp hoặc thư mục → **Copy**, quay về thư mục của bạn → chuột phải → **Paste**.
3. Trong Terminal: `cp -rn ~/work/samples/leanbot-basic ~/work/`

Notebook mở trong `samples/` vẫn **chạy được**, nhưng không lưu được (thư mục chỉ đọc). Muốn giữ kết quả, hãy sao chép trước.

## Nguồn và quyền sử dụng

Các tệp được lấy nguyên văn từ nguồn của Pythaverse (PTV), chỉ đổi những điểm ghi trong README của từng thư mục
(thêm phần mở rộng tệp, thay thông tin Wi-Fi bằng chỗ trống, đổi tên cột số hiệu robot). Bản quyền thuộc tác giả
và Pythaverse; dùng cho học tập và giảng dạy trong các khoá của Pythaverse.

| Nguồn | Phiên bản (commit) | Dùng cho |
|---|---|---|
| PGit `quang.dinh/Leanbot_Programming_Guide` (thư mục *Object Color Classification with AI Model*) | `c2ed6ed4` (master) | `leanbot-basic/` |
| GitHub `PTV-TechHub/digitaltwins-service` (`digital-twins/client/public/Demo`, `.../LeanbotCourseDemo`, `digital-twins/docs/*.csv`) | `ba552ed9` (`digital_twins_pythaverse_v1.1-prod`; giống bản đang chạy trên digitaltwin.pythaverse.space) | `digital-twin/` |
| PGit `ptvairoc/Synapsecity_Primary` | `dab7213c` (master) | `synapse-city/primary/` |
| PGit `ptvairoc/Synapsecity_Secondary` | `c0722a17` (= `b84e1a07` + thay Wi-Fi bằng chỗ trống) | `synapse-city/secondary/` |
| PGit `ptvairoc/Synapsecity_HighSchool` | `2f639804` (= `ac58d2bb` + thay Wi-Fi bằng chỗ trống) | `synapse-city/highschool/` |

**Không có trong bộ này:** dữ liệu học sinh tự thu thập (ví dụ `Lb117072_*.json` theo số hiệu robot của một người),
thông tin cá nhân, mật khẩu, token hay thông tin Wi-Fi thật.

## Cập nhật nội dung (cho nhóm nội dung / kỹ thuật)

1. Tạo nhánh, thêm/sửa tệp trong một trong ba thư mục, cập nhật README của thư mục đó (tệp gì, bài học nào dùng, cách mở)
   và bảng nguồn ở trên.
2. Mở pull request. CI (`.github/workflows/check.yml`) chạy `tools/check_samples.py` (cấu trúc, kích thước, mẫu
   bí mật/thông tin cá nhân) và gitleaks. Cần một người duyệt.
3. Sau khi merge vào `main`, máy chủ PNote tự đồng bộ trong vòng 30 phút (`sync-samples.sh` trên `.125`, xem
   `infra/gitops/pnote/samples/README.md`). Không cần build lại image hay khởi động lại hub.

Quy tắc: chỉ ba thư mục trên + README + notebook sao chép ở gốc; mỗi tệp tối đa 10 MB, tổng tối đa 100 MB; không có
liên kết tượng trưng (symlink); không dữ liệu gắn với một học sinh hoặc một robot cụ thể.

Liên quan: Pythaverse2026#631 (tệp dữ liệu trong hướng dẫn), #641 (PNote/MQTT), #652 (bộ dữ liệu mẫu này).
