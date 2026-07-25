# 🦁 Pardus Otağı (Yerel & offline Yapay Zeka Asistanı)

**Pardus Otağı**, internet bağlantısına ihtiyaç duymadan (**offline**) tamamen bilgisayarınızın **CPU/GPU** gücüyle çalışan, verilerinizi dışarı aktarmayan, güvenli ve özgür bir yapay zeka masaüstü uygulamasıdır.

Uygulama, **Ollama** altyapısını kullanarak **Pardus İşletim Sistemi** üzerinde **C++** ve **Qt6** ile geliştirilmiştir. Yerel yapay zeka modelleri (**Llama 3.2, Phi-3** vb.) sayesinde hızlı, gizlilik odaklı ve kesintisiz bir sohbet deneyimi sunar.

---

# ✨ Özellikler

- 🔒 **%100 Çevrimdışı ve Güvenli**
  - İnternet bağlantısı gerektirmez.
  - Verileriniz tamamen kendi bilgisayarınızda işlenir.
  - Hiçbir veri harici sunuculara gönderilmez.

- 🤖 **Yerel Yapay Zeka Modelleri**
  - Ollama üzerinden çalışan Llama 3.2, Phi-3 ve diğer yerel modelleri destekler.

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

# 🤖 Ollama Kurulumu

Pardus Otağı'nın çalışabilmesi için bilgisayarınızda **Ollama** kurulu olmalıdır.

## 1. Ollama Kurulumu

```bash
curl -fsSL https://ollama.com/install.sh | sh
```

---

## 2. Yapay Zeka Modeli İndirme

### Llama 3.2 (Önerilen)

```bash
ollama run llama3.2
```

### Phi-3 (Düşük Donanımlar İçin)

```bash
ollama run phi3
```

> **Not:** Model indirildikten sonra internet bağlantısını tamamen keserek uygulamayı çevrimdışı kullanabilirsiniz.

---

# 🐧 Pardus'ta Kurulum

## 1. Gerekli Paketleri Kurun

```bash
sudo apt update
sudo apt install build-essential cmake qt6-base-dev qt6-tools-dev
```

---

## 2. Projeyi Klonlayın

```bash
git clone https://github.com/gucluyurekler0/pardusotagi.git
cd pardusotagi
```

---

## 3. Derleyin

```bash
mkdir -p build
cd build
cmake ..
make
```

---

## 4. Uygulamayı Çalıştırın

```bash
./OfflineLLMApp
```

---

# 🖥️ Masaüstü Kısayolu (İsteğe Bağlı)

Pardus uygulama menüsüne eklemek için:

```bash
mkdir -p ~/.local/share/applications
nano ~/.local/share/applications/pardus-otagi.desktop
```

Aşağıdaki içeriği ekleyin:

```ini
[Desktop Entry]
Version=1.0
Type=Application
Name=Pardus Otağı
Comment=Yerel ve Çevrimdışı Yapay Zeka Asistanı
Exec=sh -c "$HOME/pardusotagi/build/OfflineLLMApp"
Terminal=false
Categories=Utility;ArtificialIntelligence;Development;
```

Dosyayı kaydedin ve aşağıdaki komutları çalıştırın:

```bash
chmod +x ~/.local/share/applications/pardus-otagi.desktop
update-desktop-database ~/.local/share/applications
```

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
- Llama 3.2
- Phi-3
- JSON
- CMake

---

# 📄 Lisans

Bu proje açık kaynak olarak geliştirilmiştir.

Katkıda bulunabilir, geliştirebilir ve kendi ihtiyaçlarınıza göre özelleştirebilirsiniz.
