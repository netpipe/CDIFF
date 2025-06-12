#include <QApplication>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

extern "C" {
    #include "gguf.h"
}
#define GGUF_VALUE_TYPE_STRING GGUF_TYPE_STRING

bool convert_to_gguf(const QString &inPath, const QString &outPath, QLabel *status) {
    QFile file(inPath);
    if (!file.open(QIODevice::ReadOnly)) {
        status->setText("❌ Failed to open input file");
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    if (data.size() < 8) {
        status->setText("❌ Invalid safetensors format");
        return false;
    }

    // Parse safetensors header
    quint64 jsonLen = *reinterpret_cast<const quint64*>(data.data());
    if (jsonLen + 8 > data.size()) {
        status->setText("❌ Header too large");
        return false;
    }

    QByteArray jsonBytes = data.mid(8, jsonLen);
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonBytes, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject()) {
        status->setText("❌ JSON parse error");
        return false;
    }

    QJsonObject obj = jsonDoc.object();
    gguf_context *ctx = gguf_init_empty();

    // Add dummy metadata
   // gguf_set_meta(ctx, "model", "converted_by", GGUF_VALUE_TYPE_STRING, "qt-safetensors");

    for (auto it = obj.begin(); it != obj.end(); ++it) {
        QString name = it.key();
        QJsonObject tensorMeta = it.value().toObject();
        quint64 offset = tensorMeta["data_offsets"].toArray()[0].toInt();
        quint64 end = tensorMeta["data_offsets"].toArray()[1].toInt();
        auto shapeArr = tensorMeta["shape"].toArray();

        std::vector<int64_t> shape;
        for (auto v : shapeArr) shape.push_back(v.toInt());

        quint64 len = end - offset;
        if (offset + len > (quint64)data.size()) {
            status->setText("❌ Tensor '" + name + "' out of bounds");
            gguf_free(ctx);
            return false;
        }

        gguf_add_tensor(ctx,
            name.toStdString().c_str(),
            data.constData() + offset,
            len,
            shape.data(),
            shape.size(),
            GGUF_TYPE_F32);  // You can detect dtype later
    }

    bool ok = gguf_save_to_file(ctx, outPath.toStdString().c_str());
    gguf_free(ctx);

    status->setText(ok ? "✅ GGUF saved" : "❌ Save failed");
    return ok;
}
