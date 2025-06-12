#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QProcess>
#include <QPixmap>
#include <QFileInfo>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QDir>
#include <QProgressBar>
#include <QFileDialog>

QString outputImagePath = "output.png";

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("Stable Diffusion GUI");

    // Prompt input
    QLineEdit *promptEdit = new QLineEdit;
    promptEdit->setPlaceholderText("Enter prompt...");

    // Negative prompt input
    QLineEdit *negPromptEdit = new QLineEdit;
    negPromptEdit->setPlaceholderText("Enter negative prompt...");

    // Width/Height
    QSpinBox *widthSpin = new QSpinBox;
    widthSpin->setRange(64, 2048);
    widthSpin->setValue(512);

    QSpinBox *heightSpin = new QSpinBox;
    heightSpin->setRange(64, 2048);
    heightSpin->setValue(512);

    // Sampling method
    QComboBox *samplingCombo = new QComboBox;
    QStringList methods = {
        "euler", "euler_a", "heun", "dpm2", "dpm++2s_a", "dpm++2m", "dpm++2mv2",
        "ipndm", "ipndm_v", "lcm", "ddim_trailing", "tcd"
    };
    samplingCombo->addItems(methods);
    samplingCombo->setCurrentText("euler_a");

    // Steps
    QSpinBox *stepsSpin = new QSpinBox;
    stepsSpin->setRange(1, 150);
    stepsSpin->setValue(20);

    // Seed
    QSpinBox *seedSpin = new QSpinBox;
    seedSpin->setRange(-1, 100000);
    seedSpin->setValue(42);

    // Threads
    QSpinBox *threadsSpin = new QSpinBox;
    threadsSpin->setRange(1, 16);
    threadsSpin->setValue(4);

    // Generate button
    QPushButton *generateBtn = new QPushButton("Generate Image");

    // Image output
    QLabel *imageLabel = new QLabel("Image will appear here");
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(256, 256);

    // Layout setup
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Prompt:"));
    layout->addWidget(promptEdit);

    layout->addWidget(new QLabel("Negative Prompt:"));
    layout->addWidget(negPromptEdit);

    QPushButton *downloadModelBtn = new QPushButton("Download Model (q4_0)");
    layout->addWidget(downloadModelBtn);

    QProgressBar *progressBar = new QProgressBar;
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    layout->addWidget(progressBar);

      //  imageLabel->setText("⚠️ Model not found. Please download it.");
        QNetworkAccessManager *manager = new QNetworkAccessManager(&window);
        QObject::connect(downloadModelBtn, &QPushButton::clicked, [&]() {
            if (!QFileInfo::exists("models/stable-diffusion-v1-5-pruned-emaonly-Q4_0.gguf")){
            QString initialUrl = "https://huggingface.co/second-state/stable-diffusion-v1-5-GGUF/resolve/main/stable-diffusion-v1-5-pruned-emaonly-Q4_0.gguf";
            QString outputDir = "models";
            QString outputFile = QApplication::applicationDirPath() + outputDir + "/stable-diffusion-v1-5-pruned-emaonly-Q4_0.gguf";

            QDir().mkpath(outputDir);
            QNetworkRequest request(initialUrl);
            QNetworkReply *reply = manager->get(request);

            QObject::connect(reply, &QNetworkReply::finished, [=]() {
                QVariant redirect = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
                if (redirect.isValid()) {
                    // Got a redirect (LFS behavior), follow it
                    QUrl redirectedUrl = redirect.toUrl();
                    QNetworkRequest newReq(redirectedUrl);
                    QNetworkReply *finalReply = manager->get(newReq);

                    QObject::connect(finalReply, &QNetworkReply::finished, [=]() {
                        if (finalReply->error() == QNetworkReply::NoError) {
                            QFile file(outputFile);
                            if (file.open(QIODevice::WriteOnly)) {
                                file.write(finalReply->readAll());
                                file.close();
                                imageLabel->setText("✅ Model downloaded after redirect!");
                            } else {
                                imageLabel->setText("❌ Failed to save redirected model.");
                            }
                        } else {
                            imageLabel->setText("❌ Redirected download failed: " + finalReply->errorString());
                        }
                        finalReply->deleteLater();
                    });
                } else {
                    // No redirect (unlikely for Hugging Face LFS)
                    if (reply->error() == QNetworkReply::NoError) {
                        QFile file(outputFile);
                        if (file.open(QIODevice::WriteOnly)) {
                            file.write(reply->readAll());
                            file.close();
                            imageLabel->setText("✅ Model downloaded directly!");
                        } else {
                            imageLabel->setText("❌ Failed to write model file.");
                        }
                    } else {
                        imageLabel->setText("❌ Download failed: " + reply->errorString());
                    }
                }
                reply->deleteLater();
            });

            imageLabel->setText("📥 Downloading model could take a while!(1.5GB)...");
            }else{  imageLabel->setText("❌ already downloaded.");}
        });


        QPushButton *saveButton = new QPushButton("💾 Save Image");
      //  saveButton->setEnabled(false); // disabled until generation is done
        layout->addWidget(saveButton);

        QObject::connect(saveButton, &QPushButton::clicked, [=]() {
            QString defaultPath = QDir::homePath() + "/image.png";
            QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Image", defaultPath, "PNG Image (*.png)");
            if (!fileName.isEmpty()) {
                QFile::copy("output.png", fileName); // or your actual output file path
            }
        });


    QHBoxLayout *sizeLayout = new QHBoxLayout;
    sizeLayout->addWidget(new QLabel("Width:"));
    sizeLayout->addWidget(widthSpin);
    sizeLayout->addWidget(new QLabel("Height:"));
    sizeLayout->addWidget(heightSpin);
    layout->addLayout(sizeLayout);

    QHBoxLayout *samplerLayout = new QHBoxLayout;
    samplerLayout->addWidget(new QLabel("Sampler:"));
    samplerLayout->addWidget(samplingCombo);
    layout->addLayout(samplerLayout);

    QHBoxLayout *stepLayout = new QHBoxLayout;
    stepLayout->addWidget(new QLabel("Steps:"));
    stepLayout->addWidget(stepsSpin);
    stepLayout->addWidget(new QLabel("Seed:"));
    stepLayout->addWidget(seedSpin);
    stepLayout->addWidget(new QLabel("Threads:"));
    stepLayout->addWidget(threadsSpin);
    layout->addLayout(stepLayout);

    layout->addWidget(generateBtn);
    layout->addWidget(imageLabel);

    window.setLayout(layout);
    window.resize(500, 700);
    window.show();

    QObject::connect(generateBtn, &QPushButton::clicked, [&]() {
        QString prompt = promptEdit->text();
        QString negPrompt = negPromptEdit->text();
        QString sampler = samplingCombo->currentText();
        int width = widthSpin->value();
        int height = heightSpin->value();
        int steps = stepsSpin->value();
        int seed = seedSpin->value();
        int threads = threadsSpin->value();

        QStringList args = {
            "-m", QApplication::applicationDirPath() + "/models/stable-diffusion-v1-5-pruned-emaonly-Q4_0.gguf",
            "-p", prompt,
            "-n", negPrompt,
            "-o", outputImagePath,
            "--width", QString::number(width),
            "--height", QString::number(height),
            "--sampling-method", sampler,
            "--steps", QString::number(steps),
            "--seed", QString::number(seed),
            "-t", QString::number(threads)
        };

        imageLabel->setText("Generating...");

        QProcess *process = new QProcess(&window);
//        QObject::connect(process, &QProcess::readyReadStandardError, [=]() {
//            QString err = process->readAllStandardError();
//            qDebug() << "stderr:" << err;
//            imageLabel->setText("⚠️ Error: " + err);
//        });
      //  qDebug() << "Running: ./sd" << args;

        QObject::connect(process, &QProcess::readyReadStandardOutput, [=]() {
            QString output = process->readAllStandardOutput();
            QTextStream stream(&output);
            while (!stream.atEnd()) {
                QString line = stream.readLine();
                qDebug() << "stdout:" << line;

                // Parse progress: "|===>...| 1/3"
                QRegularExpression progRegex(R"(\|\s*(\d+)/(\d+))");
                QRegularExpressionMatch match = progRegex.match(line);
                if (match.hasMatch()) {
                    int step = match.captured(1).toInt();
                    int total = match.captured(2).toInt();
                    if (total > 0) {
                        int percent = (step * 100) / total;
                        progressBar->setValue(percent);
                    }
                }
            }
        });


        QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                         [&](int exitCode, QProcess::ExitStatus status) {
            if (exitCode == 0 && QFileInfo::exists(outputImagePath)) {
                QPixmap img(outputImagePath);
                imageLabel->setPixmap(img.scaled(512, 512, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                imageLabel->setText("Generation failed");
            }
            process->deleteLater();
        });

    //    process->start( "." + QApplication::applicationDirPath() + "/sd", args); // Use full path if needed
     //     process->start("/bin/bash", QStringList() << QApplication::applicationDirPath() + "/sd" << args, QIODevice::ReadWrite);
          QString sdPath = QApplication::applicationDirPath() + "/sd";
          process->start(sdPath, args, QIODevice::ReadWrite);


    });

    return app.exec();
}
