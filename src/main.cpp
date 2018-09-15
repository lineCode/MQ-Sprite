#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QStatusBar>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <iostream>

QFile* sLogFile = nullptr;

void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{	
    QString ctx = QString("%1:%2").arg(context.file).arg(context.line);	
	auto logError = [ctx](const char* type, const QString& message) {
		auto* mw = MainWindow::Instance();
		if (mw != nullptr && !message.startsWith("nativeResourceForWindow")) {
			mw->showMessage(QString("[%1] %2 %3").arg(type, message, ctx), 2000);
		}
		std::cerr << "[" << type << "] " << message.toStdString() << "\n";
		if (sLogFile) {
			QTextStream out(sLogFile);
			out << "[" << type << "] " << message << "\n";
		}
	};

	auto logInfo = [](const QString& message) {
		std::cout << "[Info] " << message.toStdString() << "\n";
		if (sLogFile) {
			QTextStream out(sLogFile);
			out << "[Info] " << message << "\n";
		}
	};

    switch (type) {
	default: {
		logInfo(msg);
		break;
	}	
	case QtDebugMsg: logError("Debug", msg); break;
	case QtWarningMsg: logError("Warning", msg); break;
	case QtCriticalMsg: logError("Critical", msg); break;
	case QtFatalMsg: {
		logError("Fatal", msg);
		abort();
		break;
	}
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    // QApplication::setStyle(QStyleFactory::create("fusion"));
    QCoreApplication::setOrganizationName("Wizard Mode");
    QCoreApplication::setOrganizationDomain("playmoonquest.com");
    QCoreApplication::setApplicationName("MoonQuest Sprite Editor");
    QApplication a(argc, argv);
	
	QFile file("log.txt");
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		sLogFile = &file;

		QTextStream out(sLogFile);
		out << "MoonQuest Sprite Editor Log\n";
	}
    MainWindow w;
    w.show();
    
    return a.exec();
}
