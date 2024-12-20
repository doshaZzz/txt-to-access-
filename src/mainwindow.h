#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "wait_time.h"
#include "help.h"

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QThread>
#include <QMetaType>

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class select_file
{
public:

    //set foo
    void setkks(QString enter_kks)
    {
        this->kks = enter_kks;
    }
    void setsignal(QString enter_signal)
    {
        this->signal = enter_signal;
    }
    void setname_e(QString enter_name_e)
    {
        this->name_e = enter_name_e;
    }
    void setverwe(QString enter_verwe)
    {
        this->verwe = enter_verwe;
    }
    void setcabinet(QString enter_cabinet)
    {
        this->cabinet = enter_cabinet;
    }
    void setea(QString enter_ea)
    {
        this->ea = enter_ea;
    }
    void setopch(QString enter_opch)
    {
        this->opch = enter_opch;
    }
    void setnopch(QString enter_nopch)
    {
        this->nopch = enter_nopch;
    }
    void setbst_nr(QString enter_bst_nr)
    {
        this->bst_nr = enter_bst_nr;
    }
    void setsettings_e(QString enter_settings_e)
    {
        this->settings_e = enter_settings_e;
    }
    void setunits_e(QString enter_units_e)
    {
        this->units_e = enter_units_e;
    }
    void setmin(QString enter_min)
    {
        this->min = enter_min;
    }
    void setmax(QString enter_max)
    {
        this->max = enter_max;
    }
    void settype(QString enter_type)
    {
        this->type = enter_type;
    }
    void setkks_kl(QString enter_kks_kl)
    {
        this->kks_kl = enter_kks_kl;
    }
    void setkks_reg(QString enter_kks_reg)
    {
        this->kks_reg = enter_kks_reg;
    }
    void setkks_dat(QString enter_kks_dat)
    {
        this->kks_dat = enter_kks_dat;
    }
    void setkks_srkr(QString enter_kks_srkr)
    {
        this->kks_srkr = enter_kks_srkr;
    }
    void settime_srcr(QString enter_time_srcr)
    {
        this->time_srcr = enter_time_srcr;
    }
    void setlocation(QString enter_location)
    {
        this->location = enter_location;
    }
    void setslot_main(QString enter_slot_main)
    {
        this->slot_main = enter_slot_main;
    }
    void setslot_res(QString enter_slot_res)
    {
        this->slot_res = enter_slot_res;
    }
    void setdelta(QString enter_setdelta)
    {
        this->delta = enter_setdelta;
    }

    //get foo
    QString getkks()
    {
        return this->kks;
    }
    QString getsignal()
    {
        return this->signal;
    }
    QString getname_e()
    {
        return this->name_e;
    }
    QString getverwe()
    {
        return this->verwe;
    }
    QString getcabinet()
    {
        return this->cabinet;
    }
    QString getea()
    {
        return this->ea;
    }
    QString getopch()
    {
        return this->opch;
    }
    QString getnopch()
    {
        return this->nopch;
    }
    QString getbst_nr()
    {
        return this->bst_nr;
    }
    QString getsettings_e()
    {
        return this->settings_e;
    }
    QString getunits_e()
    {
        return this->units_e;
    }
    QString getmin()
    {
        return this->min;
    }
    QString getmax()
    {
        return this->max;
    }
    QString gettype()
    {
        return this->type;
    }
    QString getkks_kl()
    {
        return this->kks_kl;
    }
    QString getkks_reg()
    {
        return this->kks_reg;
    }
    QString getkks_dat()
    {
        return this->kks_dat;
    }
    QString getkks_srkr()
    {
        return this->kks_srkr;
    }
    QString gettime_srcr()
    {
        return this->time_srcr;
    }
    QString getlocation()
    {
        return this->location;
    }
    QString getslot_main()
    {
        return this->slot_main;
    }
    QString getslot_res()
    {
        return this->slot_res;
    }
    QString getdelta()
    {
        return this->delta;
    }
private:
    QString kks;
    QString signal;
    QString name_e;
    QString verwe;
    QString cabinet;
    QString ea;
    QString opch;
    QString nopch;
    QString bst_nr;
    QString settings_e;
    QString units_e;
    QString min;
    QString max;
    QString type;
    QString kks_kl;
    QString kks_reg;
    QString kks_dat;
    QString kks_srkr;
    QString time_srcr;
    QString location;
    QString slot_main;
    QString slot_res;
    QString delta;
};


class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject* parent = nullptr);
    void create_tables(QFile &file_log) //создание таблиц
    {
        //создаем таблицу для TBL_DOP_INF
        if(!query.exec("CREATE TABLE TBL_DOP_INF"
                        "("
                        "CABINET VARCHAR(100),"
                        "KKS VARCHAR(100),"
                        "SIGNAL VARCHAR(100),"
                        "VERWE VARCHAR(100),"
                        "OPD VARCHAR(100),"
                        "OPCH VARCHAR(100),"
                        "NOPCH VARCHAR(100),"
                        "NAME_E VARCHAR(255),"
                        "EA VARCHAR(100),"
                        "BST_NR VARCHAR(100),"
                        "SETTINGS_E VARCHAR(100),"
                        "UNITS_E VARCHAR(100),"
                        "DELTA VARCHAR(100),"
                        "MIN_ VARCHAR(100),"
                        "MAX_ VARCHAR(100));"))
        {
            //file_log.open(QIODevice::Append); //открываем новый файл  на запись
            //QTextStream in_log(&file_log); //поток в лог
            //in_log << query.lastError().databaseText()+" is not open"<< '\n'; //чтобы лог писался с новой строки
            //file_log.close();
            emit signal_wrightWidgLog(query.lastError().databaseText());
            //ui->listWidget_log->addItem(query.lastError().databaseText());
            //ui->listWidget_log->scrollToBottom();
            qDebug() << query.lastError().databaseText();
        }

        //создаем таблицу TBL_KLAPAN
        if(!query.exec("CREATE TABLE TBL_KLAPAN"
                        "("
                        "CABINET VARCHAR(100),"
                        "KL_KKS VARCHAR(100),"
                        "TRVL_TIME VARCHAR(100));"))
        {
            //file_log.open(QIODevice::Append); //открываем новый файл  на запись
            //QTextStream in_log(&file_log); //поток в лог
            //in_log << query.lastError().databaseText()+" is not open"<< '\n'; //чтобы лог писался с новой строки
            //file_log.close();
            //ui->listWidget_log->addItem(query.lastError().databaseText());
            //ui->listWidget_log->scrollToBottom();
            emit signal_wrightWidgLog(query.lastError().databaseText());
            qDebug() << query.lastError().databaseText();
        }


        //создаем таблицу TBL_KL_REG
        if(!query.exec("CREATE TABLE TBL_KL_REG"
                        "("
                        "CABINET VARCHAR(10),"
                        "EA VARCHAR(10),"
                        "KL_KKS VARCHAR(100),"
                        "REG_KKS VARCHAR(100));"))
        {
            //file_log.open(QIODevice::Append); //открываем новый файл  на запись
            //QTextStream in_log(&file_log); //поток в лог
            //in_log << query.lastError().databaseText()+" is not open"<< '\n'; //чтобы лог писался с новой строки
            //file_log.close();
            //ui->listWidget_log->addItem(query.lastError().databaseText());
            //ui->listWidget_log->scrollToBottom();
            emit signal_wrightWidgLog(query.lastError().databaseText());
            qDebug() << query.lastError().databaseText();
        }

        //создаем таблицу TBL_REGUL
        if(!query.exec("CREATE TABLE TBL_REGUL"
                        "("
                        "REG_KKS VARCHAR(100),"
                        "DAT_KKS VARCHAR(100),"
                        "EA VARCHAR(10));"))

        {
            //file_log.open(QIODevice::Append); //открываем новый файл  на запись
            //QTextStream in_log(&file_log); //поток в лог
            //in_log << query.lastError().databaseText()+" is not open"<< '\n'; //чтобы лог писался с новой строки
            //file_log.close();
            //ui->listWidget_log->addItem(query.lastError().databaseText());
            //ui->listWidget_log->scrollToBottom();
            emit signal_wrightWidgLog(query.lastError().databaseText());
            qDebug() << query.lastError().databaseText();
        }

        //создаем таблицу TBL_MODUL
        if(!query.exec("CREATE TABLE TBL_MODUL"
                        "("
                        "CABINET VARCHAR(10),"
                        "M_TYPE VARCHAR(100),"
                        "LOCATION VARCHAR(10),"
                        "PRIMARY KEY (CABINET, LOCATION));"))

        {
            //file_log.open(QIODevice::Append); //открываем новый файл  на запись
            //QTextStream in_log(&file_log); //поток в лог
            //in_log << query.lastError().databaseText()+" is not open"<< '\n'; //чтобы лог писался с новой строки
            //file_log.close();
            //ui->listWidget_log->addItem(query.lastError().databaseText());
            //ui->listWidget_log->scrollToBottom();
            emit signal_wrightWidgLog(query.lastError().databaseText());
            qDebug() << query.lastError().databaseText();
        }

        //создаем таблицу TBL_RESERV
        if(!query.exec("CREATE TABLE TBL_RESERV"
                        "("
                        "EA VARCHAR(10),"
                        "SLOT_MAIN VARCHAR(10),"
                        "SLOT_RES VARCHAR(10));"))

        {
            //file_log.open(QIODevice::Append); //открываем новый файл  на запись
            //QTextStream in_log(&file_log); //поток в лог
            //in_log << query.lastError().databaseText()+" is not open"<< '\n'; //чтобы лог писался с новой строки
            //file_log.close();
            //ui->listWidget_log->addItem(query.lastError().databaseText());
            //ui->listWidget_log->scrollToBottom();
            emit signal_wrightWidgLog(query.lastError().databaseText());
            qDebug() << query.lastError().databaseText();
        }
        //создаем таблицу TBL_VL_IVL
        if(!query.exec("CREATE TABLE TBL_VL_IVL"
                        "("
                        "KKS VARCHAR(100),"
                        "TYPE VARCHAR(100),"
                        "EA VARCHAR(10));"))

        {
            //file_log.open(QIODevice::Append); //открываем новый файл  на запись
            //QTextStream in_log(&file_log); //поток в лог
            //in_log << query.lastError().databaseText()+" is not open"<< '\n'; //чтобы лог писался с новой строки
            //file_log.close();
            //ui->listWidget_log->addItem(query.lastError().databaseText());
            //ui->listWidget_log->scrollToBottom();
            emit signal_wrightWidgLog(query.lastError().databaseText());
            qDebug() << query.lastError().databaseText();
        }

    }
    QString swap_slesh(QString path) //замена слешей для windows
    {
        for(int i = 0; i < path.size(); i++)
        {
            if(path[i] == '/')
            {
                path.replace(i, 1,"\\\\");
            }
        }
        return path;
    }
    void pause(int sec) //пауза
    {
        QTime dieTime = QTime::currentTime().addSecs(sec);
        while  (QTime::currentTime() < dieTime){
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }
    QHash<int, QString> create_hash_opch_EM() //создание хеша с opch
    {
        QHash<int, QString> opch;

        opch.insert(0,"AKS");
        opch.insert(1,"MKS");
        opch.insert(2,"FAW");
        opch.insert(3,"FBW");
        opch.insert(4,"EM");
        opch.insert(5,"ES");
        opch.insert(6,"IBR");
        opch.insert(7,"ITE");
        opch.insert(8,"IVL");
        opch.insert(9,"KO");
        opch.insert(10,"KR");
        opch.insert(11,"SR");
        opch.insert(12,"TE");
        opch.insert(13,"VL");

        return opch;
    }
    QHash<int, QString> create_hash_opch_NT() //создание хеша с opch
    {
        QHash<int, QString> opch;
        opch.insert(0,"AKS");
        opch.insert(1,"MKS");
        opch.insert(2,"ATS");
        opch.insert(3,"ESGM");
        opch.insert(4,"ESGS");
        opch.insert(5,"ESGV");
        opch.insert(6,"IBRN");
        opch.insert(7,"ITEN");
        opch.insert(8,"IVLN");
        opch.insert(9,"KOM");
        opch.insert(10,"REG");
        opch.insert(11,"CRU");
        opch.insert(12,"ICUM");
        opch.insert(13,"ICUS");
        opch.insert(14,"ICUV");
        return opch;
    }
    QHash<QString,QString> create_hash_names(QString path_names,QString number_eas, QFile &file_log) //создание хеша names
    {
        QHash<QString,QString> hash_names;
        QFile file(path_names);
        if(file.size()!=0)
        {
            if(file.open(QIODevice::ReadOnly))
            {
                QTextStream in(&file); //поток
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                //in_log << '\n'; //чтобы лог писался с новой строки
                while (!in.atEnd())
                { //заполняем хеш мапу пока файл не кончится
                    QString line = in.readLine(); //сюда будем класть прочитанные строки
                    if(!hash_names.contains(line.section('|',0,1))){ //проверяем совпадения в хеше
                        hash_names.insert(line.section('|',0,1),line); //добавляем в ключ ккс и сигнал,а в значение строку целиком в хешмап
                    }
                    else
                    {
                        in_log << "Сигнал: "<<  line.section('|',0,1) <<"; Данный сигнал не записан в базу т.к там уже имеется такой сигнал. Дубль в файле "<< path_names<< '\n';
                    }
                }
                file.close();
                file_log.close();
            }
            else
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << path_names+" is not open"<< '\n'; //чтобы лог писался с новой строки
                file.close();
                file_log.close();
                emit signal_wrightWidgLog(path_names+" is not open");
                // ui->listWidget_log->addItem(path_names+" is not open");
                // ui->listWidget_log->scrollToBottom();
                qDebug() << path_names+" is not open";
            }
            return hash_names;
        }
        return hash_names;
    }
    void create_hash_all(QHash<QString,QString> hash_names,QString enter_number_eas, QFile &file_log) //создание хеша names
    {
        for (auto i = hash_names.cbegin(), end = hash_names.cend(); i != end; ++i){
            //QString key = i.key();
            if(!hash_all.contains(i.key())){ //проверяем совпадения в хеше
                hash_all.insert(i.key(),i.value());
            } else {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << "Сигнал: "<<  i.key() <<" EAS: "+enter_number_eas+" добавлен в базу,но он уже имеется в нескольких кабинетах.\n";
                file_log.close();
            }
        }
        return;
    }
    QHash<QString,QString> create_hash_cabinets_3() //создание хеша с кабинетами
    {
        QHash<QString, QString> cabinets;
        /*птк ску ро*/
        cabinets.insert("101","30CMR01");
        cabinets.insert("102","30CMR02");
        cabinets.insert("103","30CMR03");
        cabinets.insert("104","30CMR04");
        cabinets.insert("105","30CMR05");
        cabinets.insert("106","30CMR06");
        cabinets.insert("107","30CMR07");
        cabinets.insert("108","30CMR08");
        cabinets.insert("109","30CMR09");
        cabinets.insert("210","30CMR10");
        cabinets.insert("211","30CMR11");
        cabinets.insert("212","30CMR12");
        cabinets.insert("213","30CMR13");
        cabinets.insert("214","30CMR14");
        cabinets.insert("215","30CMR15");
        cabinets.insert("216","30CMR16");
        cabinets.insert("217","30CMR17");

        /*птк ску то*/
        cabinets.insert("301","30CMT01");
        cabinets.insert("302","30CMT02");
        cabinets.insert("303","30CMT03");
        cabinets.insert("304","30CMT04");
        cabinets.insert("305","30CMT05");
        cabinets.insert("306","30CMT06");
        cabinets.insert("307","30CMT07");
        cabinets.insert("308","30CMT08");
        cabinets.insert("309","30CVT60");
        cabinets.insert("409","30CMT09");
        cabinets.insert("410","30CMT10");
        cabinets.insert("411","30CMT11");
        cabinets.insert("412","30CMT12");
        cabinets.insert("413","30CMT13");
        cabinets.insert("414","30CMT14");
        cabinets.insert("415","30CMT15");
        cabinets.insert("416","30CMT16");
        cabinets.insert("417","30CMT17");
        cabinets.insert("418","30CMT18");
        cabinets.insert("419","30CMT19");
        cabinets.insert("420","30CMT20");
        cabinets.insert("421","30CMT21");

        /*птк эчср*/
        cabinets.insert("311","30CMY01");
        cabinets.insert("312","30CMY02");
        cabinets.insert("313","30CMY03");
		
		/*птк тг*/
        cabinets.insert("401","30CMX01");
        cabinets.insert("422","30CMX01");
        cabinets.insert("402","30CMX02");

        /*птк ску во*/
        cabinets.insert("501","30CMW01");
        cabinets.insert("502","30CMW02");
        cabinets.insert("503","30CMW03");
        cabinets.insert("504","30CMW04");
        cabinets.insert("505","30CMW05");
        cabinets.insert("506","30CMW06");
        cabinets.insert("507","30CMW07");
        cabinets.insert("508","30CMW08");
        cabinets.insert("509","30CMW09");

        /*птк ску в*/
        cabinets.insert("601","30CMV01");
        cabinets.insert("602","30CMV02");
        cabinets.insert("603","30CMV03");
        cabinets.insert("604","30CMV04");
        cabinets.insert("605","30CMV05");
        cabinets.insert("606","30CMV06");
        cabinets.insert("607","30CMV07");
        cabinets.insert("608","30CMV08");
        cabinets.insert("609","30CMV09");

        /*птк ску во*/
        cabinets.insert("612","30CMS51");
        cabinets.insert("613","30CMS52");
        cabinets.insert("614","30CMS53");

        /*ТЕСТОВЫЕ*/
        cabinets.insert("406","ТЕСТ 406");
        cabinets.insert("407","ТЕСТ 407");

        return cabinets;
    }

    QHash<QString,QString> create_hash_cabinets_4() //создание хеша с кабинетами
    {
        QHash<QString, QString> cabinets;
        /*птк ску ро*/
        cabinets.insert("101","40CMR01");
        cabinets.insert("102","40CMR02");
        cabinets.insert("103","40CMR03");
        cabinets.insert("104","40CMR04");
        cabinets.insert("105","40CMR05");
        cabinets.insert("106","40CMR06");
        cabinets.insert("107","40CMR07");
        cabinets.insert("108","40CMR08");
        cabinets.insert("109","40CMR09");
        cabinets.insert("210","40CMR10");
        cabinets.insert("211","40CMR11");
        cabinets.insert("212","40CMR12");
        cabinets.insert("213","40CMR13");
        cabinets.insert("214","40CMR14");
        cabinets.insert("215","40CMR15");
        cabinets.insert("216","40CMR16");
        cabinets.insert("217","40CMR17");

        /*птк ску то*/
        cabinets.insert("301","40CMT01");
        cabinets.insert("302","40CMT02");
        cabinets.insert("303","40CMT03");
        cabinets.insert("304","40CMT04");
        cabinets.insert("305","40CMT05");
        cabinets.insert("306","40CMT06");
        cabinets.insert("307","40CMT07");
        cabinets.insert("308","40CMT08");
        cabinets.insert("309","40CVT60");
        cabinets.insert("409","40CMT09");
        cabinets.insert("410","40CMT10");
        cabinets.insert("411","40CMT11");
        cabinets.insert("412","40CMT12");
        cabinets.insert("413","40CMT13");
        cabinets.insert("414","40CMT14");
        cabinets.insert("415","40CMT15");
        cabinets.insert("416","40CMT16");
        cabinets.insert("417","40CMT17");
        cabinets.insert("418","40CMT18");
        cabinets.insert("419","40CMT19");
        cabinets.insert("420","40CMT20");
        cabinets.insert("421","40CMT21");

        /*птк эчср*/
        cabinets.insert("311","40CMY01");
        cabinets.insert("312","40CMY02");
        cabinets.insert("313","40CMY03");

        /*птк тг*/
        cabinets.insert("401","40CMX01");
        cabinets.insert("422","40CMX01");
        cabinets.insert("402","40CMX02");

        /*птк ску во*/
        cabinets.insert("501","40CMW01");
        cabinets.insert("502","40CMW02");
        cabinets.insert("503","40CMW03");
        cabinets.insert("504","40CMW04");
        cabinets.insert("505","40CMW05");
        cabinets.insert("506","40CMW06");
        cabinets.insert("507","40CMW07");
        cabinets.insert("508","40CMW08");
        cabinets.insert("509","40CMW09");

        /*птк ску в*/
        cabinets.insert("601","40CMV01");
        cabinets.insert("602","40CMV02");
        cabinets.insert("603","40CMV03");
        cabinets.insert("604","40CMV04");
        cabinets.insert("605","40CMV05");
        cabinets.insert("606","40CMV06");
        cabinets.insert("607","40CMV07");
        cabinets.insert("608","40CMV08");
        cabinets.insert("609","40CMV09");

        /*птк ску во*/
        cabinets.insert("612","40CMS51");
        cabinets.insert("613","40CMS52");
        cabinets.insert("614","40CMS53");

        /*ТЕСТОВЫЕ*/
        cabinets.insert("406","ТЕСТ 406");
        cabinets.insert("407","ТЕСТ 407");

        return cabinets;
    }

    QHash<QString,QString> create_hash_group(QString path_group1, QFile &file_log) //создание хеша aks,mks,faw,fbw,alarms,delta,ats,esgm,esgs,esgv,ibrn,iten,ivln,kom,reg,cru,icum,icus,icuv
    {
        QHash<QString,QString> hash_group1;
        QFile file(path_group1);
        if(file.size()!=0)
        {
            if(file.open(QIODevice::ReadOnly))
            {
                QTextStream in(&file); //поток
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                while (!in.atEnd())
                { //заполняем хеш мапу пока файл не кончится
                    QString line = in.readLine(); //сюда будем класть прочитанные строки
                    if(!hash_group1.contains(line.section('|',0,1))){
                        hash_group1.insert(line.section('|',0,1),line); //добавляем в ключ ккс и сигнал,а в значение строку целиком в хешмап
                    }else{
                        in_log << "Сигнал " <<  line.section('|',0,1) << "; Данный сигнал не записан в базу т.к там уже имеется такой сигнал. Дубль в файле "<< path_group1 << '\n';
                    }
                }
                file.close();
                file_log.close();
            }
            else
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << path_group1+" is not open"<< '\n'; //чтобы лог писался с новой строки
                file.close();
                file_log.close();
                //ui->listWidget_log->addItem(path_group1+" is not open");
                //ui->listWidget_log->scrollToBottom();
                qDebug() << path_group1+" is not open"<< '\n';
            }
            return hash_group1;
        }
        return hash_group1;
    }
    QHash<QString,QString> create_hash_group_one(QString path_group_one, QFile &file_log) //создание хеша res_mod,sr_kr,vl_ivl
    {
        QHash<QString,QString> hash_group_one;
        QFile file(path_group_one);
        if(file.size()!=0)
        {
            if(file.open(QIODevice::ReadOnly))
            {
                QTextStream in(&file); //поток
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                while (!in.atEnd())
                { //заполняем хеш мапу пока файл не кончится
                    QString line = in.readLine(); //сюда будем класть прочитанные строки
                    if(!hash_group_one.contains(line.section('|',0,0))){
                        hash_group_one.insert(line.section('|',0,0),line.section('|',1,1));
                    }else{
                        in_log << "Сигнал: " <<  line.section('|',0,0) << ". Данный сигнал не будет записан в базу т.к там уже имеется такой сигнал. Дубль cигнала в файле " << path_group_one << '\n';
                    }
                }
                file.close();
                file_log.close();
            }
            else
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << path_group_one+" is not open" << '\n'; //чтобы лог писался с новой строки
                file.close();
                file_log.close();
                //ui->listWidget_log->addItem(path_group_one+" is not open");
                //ui->listWidget_log->scrollToBottom();
                qDebug() << path_group_one+" is not open"<< '\n';
            }
            return hash_group_one;
        }
        return hash_group_one;
    }
    QHash<QString,QString> create_hash_group_reg(QString path_group_reg, QFile &file_log) //создание хеша kl_reg,regul
    {
        QHash<QString,QString> hash_group_reg;
        QFile file(path_group_reg);
        if(file.size()!=0)
        {
            if(file.open(QIODevice::ReadOnly))
            {
                QTextStream in(&file); //поток
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                while (!in.atEnd())
                { //заполняем хеш мапу пока файл не кончится
                    QString line = in.readLine(); //сюда будем класть прочитанные строки
                    if(!hash_group_reg.contains(line)){
                        hash_group_reg.insert(line,line);
                    }else{
                        in_log << "Регулятор: " <<  line.section('|',0,0) << ". Данный регулятор не будет записан в базу т.к там уже имеется такой регулятор. Дубль регулятора в файле " << path_group_reg << '\n';
                    }
                }
                file.close();
                file_log.close();
            }
            else
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << path_group_reg+" is not open" << '\n'; //чтобы лог писался с новой строки
                file.close();
                file_log.close();
                //ui->listWidget_log->addItem(path_group_one+" is not open");
                //ui->listWidget_log->scrollToBottom();
                qDebug() << path_group_reg+" is not open"<< '\n';
            }
            return hash_group_reg;
        }
        return hash_group_reg;
    }
    QHash<QString,QString> create_hash_group_equip(QString path_group_equip, QFile &file_log) //создание хеша em,es,ibr,ite,ivl,ko,kr,sr,te,vl
    {
        QHash<QString,QString> hash_group_equip;
        QFile file(path_group_equip);
        if(file.size()!=0)
        {
            if(file.open(QIODevice::ReadOnly))
            {
                QTextStream in(&file); //поток
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                while (!in.atEnd())
                { //заполняем хеш мапу пока файл не кончится
                    QString line = in.readLine(); //сюда будем класть прочитанные строки
                    if(!hash_group_equip.contains(line.section('|',0,0))){
                        hash_group_equip.insert(line.section('|',0,0),line);
                    }else{
                        in_log << "Сигнал : " <<  line.section('|',0,0) << ". Данный сигнал не будет записан в базу т.к там уже имеется такой сигнал. Дубль cигнала в файле " << path_group_equip<< '\n';
                    }
                }
                file.close();
                file_log.close();
            }
            else
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << path_group_equip+" is not open" << '\n'; //чтобы лог писался с новой строки
                file.close();
                file_log.close();
                //ui->listWidget_log->addItem(path_group_one+" is not open");
                //ui->listWidget_log->scrollToBottom();
                qDebug() << path_group_equip+" is not open"<< '\n';
            }
            return hash_group_equip;
        }
        return hash_group_equip;
    }
    QHash<QString,QString> create_hash_ext_mode(QString path_ext_mode,QString enter_number_eas, QFile &file_log) //создание хеша ext_mod
    {
        QHash<QString,QString> hash_ext_mode;
        QFile file(path_ext_mode);
        if(file.size()!=0)
        {
            if(file.open(QIODevice::ReadOnly))
            {
                QTextStream in(&file); //поток
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                while (!in.atEnd())
                { //заполняем хеш мапу пока файл не кончится
                    QString line = in.readLine(); //сюда будем класть прочитанные строки
                    hash_ext_mode.insert(enter_number_eas+line ,line);
                }
                file.close();
                file_log.close();
            }
            else
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << path_ext_mode+" is not open" << '\n'; //чтобы лог писался с новой строки
                file.close();
                file_log.close();
                //ui->listWidget_log->addItem(path_ext_mode+" is not open");
                //ui->listWidget_log->scrollToBottom();
                qDebug() << path_ext_mode+" is not open"<< '\n';
            }
            return hash_ext_mode;
        }
        return hash_ext_mode;
    }
    void pars_group1(QString opch, QHash<QString, QString> enter_hash, QString enter_number_eas,QFile &file_log) //парсинг[EAS].aks[EAS].mks[EAS].faw[EAS].fbw[EAS].ats
    {
        select_file file;
        QHash<QString, QString>::const_iterator j = enter_hash.constBegin();
        while (j != enter_hash.constEnd())
        {
            file.setnopch(j.value().section('|',3,3));

            file.setbst_nr(j.value().section('|',4,4));

            file.setkks(j.value().section('|',0,0));

            if(j.value().section('|',1,1) == nullptr){                  //test
                file.setsignal("-");
            } else {
                file.setsignal(j.value().section('|',1,1));
            }

            file.setopch(opch);

            query.exec("update TBL_DOP_INF "
                        "set OPCH = '"+file.getopch()+"', NOPCH = '"+file.getnopch()+"', BST_NR = '"+file.getbst_nr()+"' "
                        "where KKS='"+file.getkks()+"' AND SIGNAL='"+file.getsignal()+"' AND EA='"+enter_number_eas+"'  AND OPCH is null AND NOPCH is null AND BST_NR is null;"); //добавляем в таблицу (в столбецы (...) такие то данные(...)
            //qDebug() << "numRowsAffected = " << query.numRowsAffected();
            if(query.numRowsAffected() < 1){
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << "Сигнал: " << file.getkks() << " " << file.getsignal() <<" "<< file.getopch() <<" EAS "+enter_number_eas+". Таблица TBL_DOP_INF. Не удалось добавить сигнал в базу. Вероятно его нет в файле "+enter_number_eas+".names"<< '\n';
                qDebug() << query.lastError().databaseText();
                file_log.close();
            }
            j++;
        }
    }
    void pars_group2(QString opch, QHash<QString, QString> enter_hash, QString enter_number_eas,QFile &file_log) //парсинг[EAS].em[EAS].es[EAS].ibr[EAS].ite[EAS].ivl[EAS].ko[EAS].kr[EAS].sr[EAS].te[EAS].vl
    {
        select_file file;
        QHash<QString, QString>::const_iterator j = enter_hash.constBegin();
        while (j != enter_hash.constEnd())
        {
            file.setnopch(j.value().section('|',1,1));

            file.setbst_nr(j.value().section('|',2,2));

            file.setkks(j.value().section('|',0,0));

            file.setopch(opch);

            query.exec("update TBL_DOP_INF "
                        "set OPCH = '"+file.getopch()+"', NOPCH = '"+file.getnopch()+"', BST_NR = '"+file.getbst_nr()+"' "
                        "where KKS='"+file.getkks()+"' AND EA='"+enter_number_eas+"' AND SIGNAL ='-' AND OPCH is null AND NOPCH is null AND BST_NR is null;"); //добавляем в таблицу (в столбецы (...) такие то данные(...)
            if(query.numRowsAffected() < 1)
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << "Сигнал: " << file.getkks() <<" " << file.getopch() << " EAS "+enter_number_eas+". Таблица TBL_DOP_INF. Не удалось добавить сигнал в базу. Вероятно его нет в файле "+enter_number_eas+".names"<< '\n';
                qDebug() << query.numRowsAffected();
                file_log.close();
            }
            j++;
        }
    }
    void pars_group_te_vl(QString opch, QHash<QString, QString> enter_hash, QString enter_number_eas,QHash<QString, QString> enter_cabinets ,QHash<QString, QString> hash_names, QFile &file_log) //.te[EAS].vl .iten .ivln
    {
        select_file file;
        QHash<QString, QString>::const_iterator j = enter_hash.constBegin();
        while (j != enter_hash.constEnd())
        {
            file.setcabinet(enter_cabinets.value(enter_number_eas));

            file.setnopch(j.value().section('|',1,1));

            file.setbst_nr(j.value().section('|',2,2));

            file.setkks(j.value().section('|',0,0));

            file.setopch(opch);

            query.exec("update TBL_DOP_INF "
                       "set OPCH = '"+file.getopch()+"', NOPCH = '"+file.getnopch()+"', BST_NR = '"+file.getbst_nr()+"' "
                       "where KKS='"+file.getkks()+"' AND EA='"+enter_number_eas+"' AND SIGNAL ='-' AND OPCH is null AND NOPCH is null AND BST_NR is null;"); //добавляем в таблицу (в столбецы (...) такие то данные(...)
            if(query.numRowsAffected() < 1)
            {
                QString name_ee = hash_names.value(j.key()+'|');
                file.setname_e(name_ee.section('|',2,2));
                if(!query.exec("INSERT INTO TBL_DOP_INF (CABINET, KKS, OPCH, NOPCH, EA, BST_NR, NAME_E, SIGNAL) "
                                "VALUES('"+file.getcabinet()+"' , '"+file.getkks()+"' , '"+file.getopch()+"' , '"+file.getnopch()+"' , '"+enter_number_eas+"' , '"+file.getbst_nr()+"' , '"+file.getname_e()+"' , '-')")){ //file.getea()
                    file_log.open(QIODevice::Append); //открываем новый файл  на запись
                    QTextStream in_log(&file_log); //поток в лог
                    in_log << "Сигнал: " << file.getkks() <<" "<< file.getopch() <<"; EAS "+enter_number_eas+"; Таблица TBL_DOP_INF; Не удалось добавить сигнал в базу."<< '\n';
                    qDebug() << query.numRowsAffected();
                    file_log.close();
                }
            }
            j++;
        }
    }
    void pars_alarms(QHash<QString, QString> enter_hash, QString enter_number_eas,QFile &file_log) //парсинг[EAS].alarms
    {
        select_file file;
        QHash<QString, QString>::const_iterator j = enter_hash.constBegin();
        while (j != enter_hash.constEnd())
        {
            file.setkks(j.value().section('|',0,0));

            if(j.value().section('|',1,1) == nullptr){                  //test
                file.setsignal("-");
            } else {
                file.setsignal(j.value().section('|',1,1));
            }

            file.setsettings_e(j.value().section('|',2,2));

            file.setunits_e(j.value().section('|',5,5));

            //Убрали чтобы не записывать settings в базу
            query.exec("update TBL_DOP_INF "
                        "set SETTINGS_E = '"+file.getsettings_e()+"', UNITS_E = '"+file.getunits_e()+"' "
                        "where KKS='"+file.getkks()+"' AND SIGNAL='"+file.getsignal()+"' AND EA='"+enter_number_eas+"' AND SETTINGS_E is null AND UNITS_E is null;"); //добавляем в таблицу (в столбецы (...) такие то данные(...)
            //query.exec("update TBL_DOP_INF "
            //            "set UNITS_E = '"+file.getunits_e()+"' "
            //            "where KKS='"+file.getkks()+"' AND SIGNAL='"+file.getsignal()+"' AND EA='"+enter_number_eas+"' AND UNITS_E is null;"); //добавляем в таблицу (в столбецы (...) такие то данные(...)
            if(query.numRowsAffected() < 1)
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << "Cигнал: " << file.getkks() << " " << file.getsignal() << " EAS "+enter_number_eas+". Таблица TBL_DOP_INF. Не удалось добавить сигнал в базу. Вероятно его нет в файле "+enter_number_eas+".names"<< '\n';
                qDebug() << query.lastError().databaseText();
                file_log.close();
            }
            j++;
        }
    }
    void pars_delta(QHash<QString, QString> enter_hash, QString enter_number_eas,QFile &file_log) //парсинг[EAS].alarms
    {
        select_file file;
        QHash<QString, QString>::const_iterator j = enter_hash.constBegin();
        while (j != enter_hash.constEnd())
        {
            file.setkks(j.value().section('|',0,0));

            if(j.value().section('|',1,1) == nullptr){                  //test
                file.setsignal("-");
            } else {
                file.setsignal(j.value().section('|',1,1));
            }

            file.setmin(j.value().section('|',3,3));

            file.setmax(j.value().section('|',4,4));

            file.setunits_e(j.value().section('|',5,5));

            file.setdelta(j.value().section('|',2,2));

            if(file.getdelta() == ""){
                bool ok1;
                bool ok2;
                float min = file.getmin().toFloat(&ok1);
                float max = file.getmax().toFloat(&ok2);
                float delta_f = (max - min)/100;
                file.setdelta(QString::number(delta_f));
            }

            query.exec("update TBL_DOP_INF "
                       "set MIN_ = '"+file.getmin()+"', MAX_ = '"+file.getmax()+"', UNITS_E = '"+file.getunits_e()+"', DELTA = '"+file.getdelta()+"'  "
                        "where KKS='"+file.getkks()+"' AND SIGNAL='"+file.getsignal()+"' AND EA='"+enter_number_eas+"' AND MIN_ is null AND MAX_ is null AND UNITS_E is null AND DELTA is null;"); //добавляем в таблицу (в столбецы (...) такие то данные(...)
            if(query.numRowsAffected() < 1)
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << "Cигнал: " << file.getkks() << " " << file.getsignal() << " EAS "+enter_number_eas+". Таблица TBL_DOP_INF. Не удалось добавить сигнал в базу. Вероятно его нет в файле "+enter_number_eas+".names"<< '\n';
                qDebug() << query.lastError().databaseText();
                file_log.close();
            }
            j++;
        }
    }
    void pars_kl_reg(QHash<QString, QString> enter_hash, QString enter_number_eas,QHash<QString, QString> enter_cabinets,QFile &file_log) //парсинг[EAS].kl_reg
    {
        select_file file;
        QHash<QString, QString>::const_iterator j = enter_hash.constBegin();
        while (j != enter_hash.constEnd())
        {
            file.setcabinet(enter_cabinets.value(enter_number_eas));

            file.setkks_reg(j.key().section('|',1,1));

            file.setkks_kl(j.key().section('|',0,0));

            if(!query.exec("INSERT INTO TBL_KL_REG (CABINET, EA, KL_KKS, REG_KKS) "
                            "VALUES('"+file.getcabinet()+"', '"+enter_number_eas+"' , '"+file.getkks_kl()+"' , '"+file.getkks_reg()+"')")) //добавляем в таблицу (в столбецы (...) такие то данные(...)
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << "Сигналы: KL - "+file.getkks_kl()+" и REG - "+file.getkks_reg()+" EAS "+enter_number_eas+".Таблица TBL_KL_REG. Сгналы не записались в базу"<< '\n';
                qDebug() << query.lastError().databaseText();
                file_log.close();
            }
            j++;
        }
    }
    void pars_sr_kr(QHash<QString, QString> enter_hash, QString enter_number_eas,QHash<QString, QString> enter_cabinets,QFile &file_log) //парсинг[EAS].sr_cr
    {
        select_file file;
        QHash<QString, QString>::const_iterator j = enter_hash.constBegin();
        while (j != enter_hash.constEnd())
        {
            file.setcabinet(enter_cabinets.value(enter_number_eas));

            file.setkks_srkr(j.key());

            file.settime_srcr(j.value());

            if(!query.exec("INSERT INTO TBL_KLAPAN (CABINET, KL_KKS, TRVL_TIME) "
                            "VALUES('"+file.getcabinet()+"', '"+file.getkks_srkr()+"' , '"+file.gettime_srcr()+"')")) //добавляем в таблицу (в столбецы (...) такие то данные(...)
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << "Сигнал: "<< file.getkks_srkr() <<" EAS "+enter_number_eas+". Таблица TBL_KLAPAN. Не удалось добавить сигнал в базу. " << '\n';
                qDebug() << query.lastError().databaseText();
                file_log.close();
            }
            j++;
        }
    }
    void pars_ext_mode(QHash<QString, QString> enter_hash, QString enter_number_eas,QHash<QString, QString> enter_cabinets,QFile &file_log) //парсинг[EAS].ext_mode
    {
        select_file file;
        QHash<QString, QString>::const_iterator j = enter_hash.constBegin();
        while (j != enter_hash.constEnd())
        {
            file.setcabinet(enter_cabinets.value(enter_number_eas));

            file.setlocation(j.value());

            if(!query.exec("INSERT INTO TBL_MODUL (LOCATION, CABINET) "
                            "VALUES('"+file.getlocation()+"' , '"+file.getcabinet()+"')")) //добавляем в таблицу (в столбецы (...) такие то данные(...)
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << "EAS "+enter_number_eas+". Таблица TBL_MODUL. Данный модуль не записался в таблицу:" << file.getlocation() << " " << file.getcabinet() << '\n';
                qDebug() << query.lastError().databaseText();
                file_log.close();
            }
            j++;
        }
    }
    void pars_regul(QHash<QString, QString> enter_hash, QString enter_number_eas,QFile &file_log) //парсинг[EAS].regul
    {
        select_file file;
        QHash<QString, QString>::const_iterator j = enter_hash.constBegin();
        while (j != enter_hash.constEnd())
        {
            file.setkks_reg(j.key().section('|',0,0));

            file.setkks_dat(j.key().section('|',1,1));

            if(!query.exec("INSERT INTO TBL_REGUL (REG_KKS, DAT_KKS, EA) "
                            "VALUES('"+file.getkks_reg()+"' , '"+file.getkks_dat()+"' , '"+enter_number_eas+"')")) //добавляем в таблицу (в столбецы (...) такие то данные(...)
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << "Регулятор: "+file.getkks_reg()+" и параметр "+file.getkks_dat()+" EAS "+enter_number_eas+". Таблица TBL_REGUL. Не удалось добавить в базу"<< '\n';
                qDebug() << query.lastError().databaseText();
                file_log.close();
            }
            j++;
        }
    }
    void pars_res_mod(QHash<QString, QString> enter_hash, QString enter_number_eas,QFile &file_log) //парсинг[EAS].res_mod
    {
        select_file file;
        QHash<QString, QString>::const_iterator j = enter_hash.constBegin();
        while (j != enter_hash.constEnd())
        {

            file.setslot_main(j.key());

            file.setslot_res(j.value());

            if(!query.exec("INSERT INTO TBL_RESERV (EA, SLOT_MAIN, SLOT_RES) "
                            "VALUES('"+enter_number_eas+"' , '"+file.getslot_main()+"' , '"+file.getslot_res()+"')")) //добавляем в таблицу (в столбецы (...) такие то данные(...)
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << "Слоты: " +file.getslot_main()+" и "+file.getslot_res()+" EAS "+enter_number_eas+". Таблица TBL_RESERV.  Не удалось добавить в базу"<< '\n';
                qDebug() << query.lastError().databaseText();
                file_log.close();
            }
            j++;
        }
    }
    void pars_vl_ivl(QHash<QString, QString> enter_hash, QString enter_number_eas,QFile &file_log) //парсинг[EAS].vl_ivl
    {
        select_file file;
        QHash<QString, QString>::const_iterator j = enter_hash.constBegin();
        while (j != enter_hash.constEnd())
        {

            file.setkks(j.key());

            file.settype(j.value());

            if(!query.exec("INSERT INTO TBL_VL_IVL (KKS, TYPE, EA) "
                            "VALUES('"+file.getkks()+"' , '"+file.gettype()+"' , '"+enter_number_eas+"')")) //добавляем в таблицу (в столбецы (...) такие то данные(...)
            {
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log << "Сигнал: " +file.getkks()+" EAS "+file.getea()+". Таблица TBL_VL_IVL.  Не удалось добавить сигнал в базу"<< '\n';
                qDebug() << query.lastError().databaseText();
                file_log.close();
            }
            j++;
        }
    }
    void pars_names(QHash<QString, QString> enter_hash_names, QString enter_number_eas,QHash<QString, QString> enter_cabinets, QFile &file_log) //парсинг файлов и запрос к бд
    {
        select_file names; //создали обьект файла неймс
        QHash<QString, QString>::const_iterator j = enter_hash_names.constBegin();
        while (j != enter_hash_names.constEnd())
        {
            names.setea(enter_number_eas);

            names.setcabinet(enter_cabinets.value(enter_number_eas));

            names.setkks(j.value().section('|',0,0));

            if(j.value().section('|',1,1) == nullptr){                  //test
                names.setsignal("-");
            } else {
                names.setsignal(j.value().section('|',1,1));
            }

            names.setname_e(j.value().section('|',2,2));

            names.setverwe(j.value().section('|',3,3));
            //Изменили,чтобы не записывать в базу name_e
            if(!query.exec("INSERT INTO TBL_DOP_INF (CABINET, KKS, SIGNAL, NAME_E, VERWE, EA) "
                            "VALUES('"+names.getcabinet()+"' ,'"+names.getkks()+"' , '"+names.getsignal()+"' , '"+names.getname_e()+"' , '"+names.getverwe()+"' , '"+names.getea()+"')")) //добавляем в таблицу (в столбецы (...) такие то данные(...)
            //if(!query.exec("INSERT INTO TBL_DOP_INF (CABINET, KKS, SIGNAL, VERWE, EA) "
            //                "VALUES('"+names.getcabinet()+"' ,'"+names.getkks()+"' , '"+names.getsignal()+"' , '"+names.getverwe()+"' , '"+names.getea()+"')")) //добавляем в таблицу (в столбецы (...) такие то данные(...)
            {
                qDebug() << query.lastError().databaseText();
                file_log.open(QIODevice::Append); //открываем новый файл  на запись
                QTextStream in_log(&file_log); //поток в лог
                in_log <<"Сигнал: "<<names.getkks()<<" "<< names.getsignal() << "EAS "+names.getea()+".Таблица TBL_DOP_INF. Не удалось добавить сигнал в базу из файла "<< enter_number_eas<<".names"<<  '\n';
                file_log.close();
            }
            j++;
        }
    }

public slots:
    void slot_operationEM(QString dirSelect, QSqlDatabase db);
    void slot_operationNT(QString dirSelect, QSqlDatabase db);
signals:
    void signal_closeWait();
    void signal_wrightWidgLog(QString);
private:
    QVector<QString> select_all_EM{".aks",".mks",".faw",".fbw",".em",".es",".ibr", ".ite", ".ivl", ".ko", ".kr",".sr", ".te", ".vl",
                                   ".alarms" , ".delta",".kl_reg" , ".sr_kr" , ".ext_mod", ".regul" , ".res_mod" , ".vl_ivl" , ".daq"}; //список всех расширений select_all без names для ТПТС ЕМ
    QVector<QString> select_all_NT{".aks",".mks",".ats",".esgm",".esgs",".esgv", ".ibrn", ".iten", ".ivln", ".kom",".reg", ".cru", ".icum", ".icus", ".icuv",
                                   ".alarms" , ".delta",".kl_reg" , ".sr_kr" , ".regul" , ".res_mod" , ".vl_ivl" , ".daq"}; //список всех расширений select_all без names для ТПТС НТ
    QString dir_select = nullptr; //путь к директории с селектами
    QString data_base = " ";  //путь к файлу базы данных
    QSqlDatabase db; //обьект база данных
    QSqlQuery query; //обьект запроса к бд
    QHash<QString,QString> hash_all;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString swap_slesh(QString path) //замена слешей для windows
    {
        for(int i = 0; i < path.size(); i++)
        {
            if(path[i] == '/')
            {
                path.replace(i, 1,"\\\\");
            }
        }
        return path;
    }
    void del_table(QString name_table) //функция удаления таблицы
    {
        if(!query.exec("DROP TABLE "+name_table+"")) //удаление таблицы из бд
        {
            ui->listWidget_log ->addItem(query.lastError().databaseText());
            ui->listWidget_log->scrollToBottom();
        }
        else
        {
            ui->listWidget_log->addItem("Таблица "+name_table+" удалена");
            ui->listWidget_log->scrollToBottom();
            qDebug() << "Таблица "+name_table+" удалена";
        }
    }

public slots:
    void slot_closeWait();

    void slot_wrightWidgLog(QString);
private slots:
    void on_button_dir_db_clicked();

    void on_button_dir_selects_clicked();

    void on_button_clear_db_clicked();

    void on_button_start_clicked();

    void on_pushButton_clicked(); //кнопка i

signals:
    void signal_operationEM(QString, QSqlDatabase);
    void signal_operationNT(QString,QSqlDatabase);
private:
    Ui::MainWindow* ui;
    wait_time* wait; //обьект класса второго окна
    help* open_help;
    Worker* pW;
    QString dir_select = nullptr; //путь к директории с селектами
    QString data_base = " ";  //путь к файлу базы данных
    // QString path_log;
    QSqlDatabase db; //обьект база данных
    QSqlQuery query; //обьект запроса к бд
    // QVector<QString> select_all_EM{".aks",".mks",".faw",".fbw",".em",".es",".ibr", ".ite", ".ivl", ".ko", ".kr",".sr", ".te", ".vl",
    //                                ".alarms" , ".delta",".kl_reg" , ".sr_kr" , ".ext_mod", ".regul" , ".res_mod" , ".vl_ivl" , ".daq"}; //список всех расширений select_all без names для ТПТС ЕМ
    // QVector<QString> select_all_NT{".aks",".mks",".ats",".esgm",".esgs",".esgv", ".ibrn", ".iten", ".ivln", ".kom",".reg", ".cru", ".icum", ".icus", ".icuv",
    //                                ".alarms" , ".delta",".kl_reg" , ".sr_kr" , ".regul" , ".res_mod" , ".vl_ivl" , ".daq"}; //список всех расширений select_all без names для ТПТС НТ
    QThread* pThread;
//    QHash<QString,QString> hash_names;
};

#endif // MAINWINDOW_H
