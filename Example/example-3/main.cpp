#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>

#define Q(x) #x
#define QUOTE(x) Q(x)

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // Path to module componnents
    engine.addImportPath(QCoreApplication::applicationDirPath () +
                         "/../../../../qml-neumorphism/");
    engine.addPluginPath(QCoreApplication::applicationDirPath () +
                         "/../../../Neumorphism/debug");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}