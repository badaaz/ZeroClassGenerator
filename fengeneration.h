#ifndef FENGENERATION_H
#define FENGENERATION_H

#include <QApplication>
#include <QDialog>
#include <QTextEdit>
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>
#include <QLabel>


class FenGeneration : public QDialog
{
    Q_OBJECT

    public:
    FenGeneration(QString h,QString cpp);
    void creationOnglet(QTextEdit *widget, QString contenu, QString nom);

    public slots:
    void saveFiles();

    private:
    QTextEdit *m_textH;
    QTextEdit *m_textCpp;
    QFontMetrics *m_fm;
    QFont *m_font;
    QTabWidget *m_onglets;

};

#endif // FENGENERATION_H
