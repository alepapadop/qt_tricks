#include "mainwindow.h"
#include <QApplication>
#include <QTextBrowser>
#include <QString>
#include <QDebug>

static void openTableTag(QString *str, char *p_priority, int n)
{
    str->append("<table ");
    if (p_priority) {
        str->append(p_priority);
    }
    str->append(">");
    if (n) {
        str->append("\n");
    }
}

static void closeTableTag(QString *str, int n)
{
    str->append("</table>");
    if (n) {
        str->append("\n");
    }
}


static void openTrTag(QString *str, char *p_priority,int n)
{
    str->append("<tr ");
    if (p_priority) {
        str->append(p_priority);
    }
    str->append(">");
    if (n) {
        str->append("\n");
    }
}

static void closeTrTag(QString *str, int n)
{
    str->append("</tr>");
    if (n) {
        str->append("\n");
    }
}

static void openTdTag(QString *str, char *p_priority,int n)
{
    str->append("<td ");
    if (p_priority) {
        str->append(p_priority);
    }
    str->append(">");
    if (n) {
        str->append("\n");
    }
}

static void closeTdTag(QString *str, int n)
{
    str->append("</td>");
    if (n) {
        str->append("\n");
    }
}

static void createRowLabels(QString *str, char *label)
{

        openTdTag(str, NULL, 1);
        openTableTag(str,"height=\"50\" width=\"50\" border=\"1\" cellspacing=\"1\"", 1);
        openTrTag(str, NULL, 1);
        openTdTag(str,NULL,1);
        str->append(label);
        closeTdTag(str,1);
        closeTrTag(str, 1);
        closeTableTag(str, 1);
        closeTdTag(str, 1);


}

static void createColumnLabels(QString *str, char *label)
{
    int i = 0;

    openTrTag(str, NULL, 1);
    for (i = 0; i < 5; i++) {
        openTdTag(str, NULL, 1);
        str->append("a");
        closeTdTag(str, 1);
    }
    closeTrTag(str, 1);
}

static void createTableGrid(QString *str, double *perc)
{
    int i = 0;
    int j = 0;
    char buffer[256];

    for (i = 0; i < 10; i++) {
        openTrTag(str, NULL, 1);



        for (j = 0; j < 6; j++) {

            if (j == 0) {
                sprintf(buffer, "%d", 100 - i*10);
                //createRowLabels(str, buffer);

            } else {

                openTdTag(str, NULL, 1);
                if (perc[j - 1] >= (100 - i * 10))
                    openTableTag(str, "width=\"50\" height =\"50\" bgcolor=\"red\" cellspacing =\"0\" cellspan = \"0\" border=\"0\""  ,1);
                else
                    openTableTag(str, "width=\"50\" height =\"50\" bgcolor=\"white\" cellspacing =\"0\" cellspan = \"0\" border=\"0\""  ,1);
                openTrTag(str, NULL, 1);
                openTdTag(str,NULL,1);
                closeTdTag(str,1);
                closeTrTag(str, 1);
                closeTableTag(str, 1);
                closeTdTag(str, 1);
            }
        }
        closeTrTag(str, 1);
    }
    createColumnLabels(str, NULL);
}

static void createChart(QString *str, double *perc)
{
    openTableTag(str, "cellpadding =\"0\" cellspacing = \"0\" border=\"0\"", 1);
    createTableGrid(str, perc);
    closeTableTag(str, 1);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTextBrowser browser;
    QString str;

    double perc[] = {20, 30, 90, 60, 10};

    createChart(&str, perc);

    browser.append(str);

    w.setCentralWidget(&browser);

    w.show();

    qDebug() << str;

    return a.exec();
}


