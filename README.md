# 🦁 Pardus Otağı (Yerel & Offline Yapay Zeka Asistanı)

**Pardus Otağı**, internet bağlantısına ihtiyaç duymadan (**offline**) tamamen bilgisayarınızın **CPU/GPU** gücüyle çalışan, verilerinizi dışarı aktarmayan, güvenli ve özgür bir yapay zeka masaüstü uygulamasıdır.

Uygulama, **Ollama** altyapısını kullanarak **Pardus İşletim Sistemi** üzerinde **C++** ve **Qt6** ile geliştirilmiştir. Yerel yapay zeka modelleri (**Qwen 2.5, Llama 3.2, Phi-3** vb.) sayesinde hızlı, gizlilik odaklı ve kesintisiz bir sohbet deneyimi sunar.

---

# ✨ Özellikler

- 🔒 **%100 Çevrimdışı ve Güvenli**
  - İnternet bağlantısı gerektirmez.
  - Verileriniz tamamen kendi bilgisayarınızda işlenir.
  - Hiçbir veri harici sunuculara gönderilmez.

- 🤖 **Esnek ve Yerel Yapay Zeka Modelleri**
  - Varsayılan olarak yüksek Türkçe başarısına sahip **Qwen 2.5 (7B)** modelini kullanır.
  - Kod üzerinden istenilen diğer yerel Ollama modellerine kolayca geçiş yapılabilir.

- 💬 **Otomatik Sohbet Başlığı**
  - Yeni oluşturulan her sohbetin ilk mesajına göre yapay zeka otomatik başlık üretir.

- 📚 **Sohbet Geçmişi**
  - Tüm konuşmalar JSON formatında yerel diskte güvenle saklanır.

- 📂 **Kolay Sohbet Yönetimi**
  - Sol panelden eski konuşmalara tek tıklamayla erişebilirsiniz.
  - İstediğiniz zaman yeni sohbet başlatabilirsiniz.

- ⚡ **Yüksek Performans**
  - C++ ve Qt6 ile geliştirilmiş hafif ve hızlı masaüstü uygulaması.

---

# 🤖 Ollama Kurulumu & Model Seçimi

Pardus Otağı'nın çalışabilmesi için bilgisayarınızda **Ollama** kurulu olmalı ve tercih edilen yapay zeka modeli indirilmiş olmalıdır.

## 1. Ollama Kurulumu

curl -fsSL https://ollama.com/install.sh | sh

---

## 2. Yapay Zeka Modeli İndirme

### Qwen 2.5:7b (Varsayılan ve Önerilen)
Yüksek Türkçe dil hakimiyeti ve akıl yürütme becerisi nedeniyle projenin varsayılan modelidir:

ollama run qwen2.5:7b

### Alternatif Modeller (Gereksinime Göre)

- **Llama 3.2 (Eski Varsayılan / Standart Dengeli Model):**
  ollama run llama3.2

- **Qwen 2.5 (3B) / Phi-3 (Düşük RAM / Donanımlar İçin):**
  ollama run qwen2.5:3b
  # VEYA
  ollama run phi3

- **DeepSeek R1 (Kodlama ve Mantık Odaklı):**
  ollama run deepseek-r1:8b

> **Not:** Tercih ettiğiniz model indirildikten sonra internet bağlantısını tamamen keserek uygulamayı çevrimdışı kullanabilirsiniz.

---

# ⚙️ Farklı Bir Model Nasıl Kullanılır? (Modeller Arası Geçiş)

Uygulamanın kullandığı yapay zeka modelini veya eski sürümlerdeki **Llama 3.2** modelini tekrar kullanmak isterseniz `mainwindow.cpp` dosyasında küçük bir değişiklik yapmanız yeterlidir:

1. **`mainwindow.cpp`** dosyasını açın.
2. `on_sendButton_clicked` ve `generateTitleForChat` fonksiyonları içerisindeki `json["model"]` satırlarını bulun.
3. Model adını istediğiniz Ollama modeliyle değiştirin:

// Varsayılan Güncel Kullanım (Qwen 2.5):
json["model"] = "qwen2.5:7b";

// Eski Sürüme (Llama 3.2) Dönmek İsterseniz:
// json["model"] = "llama3.2";

// Düşük Sistemler İçin (Qwen 2.5 3B):
// json["model"] = "qwen2.5:3b";

4. Değişikliği kaydettikten sonra projeyi yeniden derleyin (`make`).

---

# 🐧 Pardus'ta Kurulum

## 1. Gerekli Paketleri Kurun

sudo apt update
sudo apt install build-essential cmake qt6-base-dev qt6-tools-dev

---

## 2. Projeyi Klonlayın

git clone https://github.com/gucluyurekler0/pardusotagi.git
cd pardusotagi

---

## 3. Derleyin

mkdir -p build
cd build
cmake ..
make

---

## 4. Uygulamayı Çalıştırın

./OfflineLLMApp

---

# 🖥️ Masaüstü Kısayolu (İsteğe Bağlı)

Pardus uygulama menüsüne eklemek için:

mkdir -p ~/.local/share/applications
nano ~/.local/share/applications/pardus-otagi.desktop

Aşağıdaki içeriği ekleyin:

[Desktop Entry]
Version=1.0
Type=Application
Name=Pardus Otağı
Comment=Yerel ve Çevrimdışı Yapay Zeka Asistanı
Exec=sh -c "$HOME/pardusotagi/build/OfflineLLMApp"
Terminal=false
Categories=Utility;ArtificialIntelligence;Development;

Dosyayı kaydedin ve aşağıdaki komutları çalıştırın:

chmod +x ~/.local/share/applications/pardus-otagi.desktop
update-desktop-database ~/.local/share/applications

---

# 📱 Kullanım

1. Ollama servisinin çalıştığından emin olun.
2. Pardus Otağı uygulamasını başlatın.
3. Alt taraftaki metin kutusuna sorunuzu yazın.
4. **Enter** tuşuna basın veya **Gönder** düğmesine tıklayın.
5. Yapay zeka ilk mesajınıza göre otomatik sohbet başlığı oluşturacaktır.
6. Sohbet geçmişiniz otomatik olarak kaydedilir.
7. Sol panelde bulunan **+ Yeni Sohbet** düğmesi ile istediğiniz zaman yeni bir konuşma başlatabilirsiniz.

---

# 🛠️ Kullanılan Teknolojiler

- C++
- Qt6
- Ollama
- Qwen 2.5 / Llama 3.2 / Phi-3
- JSON
- CMake

---

# 📄 Lisans

Bu proje açık kaynak olarak geliştirilmiştir.

Katkıda bulunabilir, geliştirebilir ve kendi ihtiyaçlarınıza göre özelleştirebilirsiniz.