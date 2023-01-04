#include "demo.h"

#include <entity/landcell.h>
#include <utils/mutils.h>

#include <QColor>
#include <QDebug>
#include <QProcess>
#include <QTime>
#include <iostream>
using namespace std;
void DEMO::demo() {
    for (int i = 0; i < 100; i++) {
        qDebug() << MUTILS::getRandIntInRange(0, 3);
    }
}

void DEMO::demoCallPython() {
    //    QProcess *m_process = new QProcess(0);
    //    m_process->setProcessChannelMode(QProcess::MergedChannels);
    //    m_process->setReadChannel(QProcess::StandardOutput);
    //    QString program = "python -V";
    //    qDebug() << program;
    //    qDebug() << m_process->state();
    //    m_process->start(program);

    QProcess p(0);
    p.start("cmd");
    p.waitForStarted();
    p.write("conda env list\n");
    p.write("python -V\n");
    p.write("conda activate devEnv\n");
    p.write("conda env list\n");
    //    p.write("ping www.baidu.com\n");
    p.closeWriteChannel();

    //    p.waitForFinished();
    //    //    qDebug().noquote() << QString::fromLocal8Bit(p.readAllStandardOutput());
    //    qDebug() << QString::fromLocal8Bit(p.readAllStandardOutput().data());
    // ============ 获取中断的持续输出 ===========
    QObject::connect(&p, &QProcess::readyReadStandardOutput, [&]() {
        qDebug() << "readyReadStandardOutput:" << QString::fromLocal8Bit(p.readAllStandardOutput().data()).trimmed();
    });

    QObject::connect(&p, &QProcess::readyReadStandardError,
        [&]() { qDebug() << "readAllStandardError:" << p.readAllStandardError().data(); });

    p.waitForFinished();
}

void DEMO::demoCallPythonEnv() {
    QProcess p(0);

    // python 的路径
    QString envName       = "devEnv";
    QString condaPath     = "F:\\software\\devSoftwares\\anaconda";
    QString condaEnvPath  = condaPath + "\\envs";
    QString pythonHome    = condaEnvPath + "\\" + envName;
    QString pythonPath    = pythonHome + "\\Lib";
    QString pythonExePath = pythonHome + "\\python.exe";

    qDebug() << pythonHome;
    qDebug() << pythonPath;
    qDebug() << pythonExePath;

    // python项目路径
    QString projectPath = "E:\\project\\linux_project\\flus_release\\win";

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    //    QProcessEnvironment env;  //有时候要用这个空环境变量才行，否则可能会出现一些污染的问题
    env.insert("PYTHONHOME", pythonHome);
    env.insert("PYTHONPATH", pythonPath);
    p.setProcessEnvironment(env);

    // 设置工作目录
    p.setWorkingDirectory(projectPath);

    // 要执行的文件及其参数
    QString     pythonScript = projectPath + "/win_main.py";
    QStringList params;
    // 配置文件路径
    QString configPath = "E:\\project\\linux_project\\flus_release\\win\\test_demo\\dg_demo\\ann_config.json";
    params << pythonScript << "--mode=ann"
           << "--config=" + configPath;
    qDebug() << params;
    p.start(pythonExePath, params);
    qDebug() << p.state();

    // ========== 运行完才输出 ============
    //    p.waitForFinished(-1);
    //    QString p_stdout = QString::fromLocal8Bit(p.readAllStandardOutput());

    //    //    QString p_stdout = p.readAll();

    //    QString p_stderr = p.readAllStandardError();
    //    if (!p_stderr.isEmpty()) qDebug().noquote() << "Python error:" << p_stderr;
    //    qDebug() << "Python result=" << p_stdout;

    //    qDebug() << p_stdout;

    // ============ 获取中断的持续输出 ===========
    QObject::connect(&p, &QProcess::readyReadStandardOutput,
        [&]() { qDebug() << "readyReadStandardOutput:" << p.readAllStandardOutput().data(); });

    QObject::connect(&p, &QProcess::readyReadStandardError,
        [&]() { qDebug() << "readAllStandardError:" << p.readAllStandardError().data(); });
    p.waitForFinished(-1);  // 一定要等脚本运行完毕，不然主程序会提前终止，脚本在后台依然运行
}

void DEMO::demoColor() {
    QColor c(255, 0, 255);
    // QColor >> QRgb(uint)
    QRgb mRgb = qRgb(c.red(), c.green(), c.blue());
    // QRgb(uint) >> QColor;
    QColor mColor = QColor(mRgb);
    // QRgb(uint) >> QString;
    QString mRgbStr = QString::number(mRgb, 16);
    // QString >> unint >> QColor
    QColor color2(mRgbStr.toUInt(NULL, 16));

    qDebug() << mRgb << mColor << mRgbStr;
}

void DEMO::demoReadDirs() {
    QString path = "D:\\litao\\learnMaterial\\ug3\\Land_simulation\\experiment\\datas\\dg_demo\\exp_config\\ann_ca";
    CBatchCaSimConfig cb(path, 5);
}

void DEMO::demoJson() {}
