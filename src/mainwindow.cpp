#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setStyleSheet("background-color: blue;");
    open_help = new help;
    //open_help->setModal(true);
    wait = new wait_time; //инициализируем обьект окна
    wait->setModal(true); //делаем окно модальным,чтобы блокировались остальные окна
    pThread = new QThread(this);
    connect(this, SIGNAL(destroyed()),
            pThread,SLOT(quit()));//для удалния потока
    pW = new Worker();
    connect(this, SIGNAL(signal_operationEM(QString,QSqlDatabase)),
            pW,SLOT(slot_operationEM(QString,QSqlDatabase)));//связали сигнал, который будет вызвывать слот(функцию)
    connect(this, SIGNAL(signal_operationNT(QString,QSqlDatabase)),
            pW,SLOT(slot_operationNT(QString,QSqlDatabase)));//связали сигнал, который будет вызвывать слот(функцию)
    connect(pW, SIGNAL(signal_closeWait()),
            this,SLOT(slot_closeWait()));//связали сигнал, который будет вызвывать слот(функцию)
    connect(pW, SIGNAL(signal_wrightWidgLog(QString)),
            this,SLOT(slot_wrightWidgLog(QString)));//связали сигнал, который будет вызвывать слот(функцию)
    pW->moveToThread(pThread);//поместили функцию в созданный поток
    pThread->start(); //запускаем цикл обработки сообщений в потоке
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_closeWait()
{
    wait->close();
    ui->listWidget_log ->addItem("Готово");
    ui->listWidget_log->scrollToBottom();
}

void MainWindow::slot_wrightWidgLog(QString messeg)
{
    ui->listWidget_log ->addItem(messeg);
    ui->listWidget_log->scrollToBottom();
}

Worker::Worker(QObject *parent) : QObject(parent){} //можно не трогать

void Worker::slot_operationEM(QString dir_select, QSqlDatabase db)
{
    query = QSqlQuery(db); //создаем экземпляр обьекта запроса и привязываем его к БД
    QFile file_log(dir_select+'-'+"log.txt"); //создаем новый файл для хранения log
    QFile &rfile_log = file_log; //создаем ссылку на лог файл для передачи в функцию
    QHash<QString, QString> cabinets = create_hash_cabinets_3(); //создаем hash c кабинетами
    create_tables(rfile_log); //создаем таблицы в бд
    QList<QString> select_names = QDir(dir_select).entryList(QStringList("*.names")); //показывает все файлы в директории c расширением *.names
    QString dir_select_for_log = dir_select;
    dir_select = dir_select.append("\\\\");
    for (int i = 0; i < select_names.size(); i++) //проход по всем файлам неймс
    {
        QString number_eas = select_names[i].left(3); //сохраняем первые три цифры из .names [EAS]
        qDebug() << "number_eas: " << number_eas;
        emit signal_wrightWidgLog("EAS "+number_eas+" обработан");
        QHash<int,QString> opch = create_hash_opch_EM(); //создали хеш opch
        /*------------------------------------------------------.names--------------------------------------------*/
        QString path_names = dir_select + select_names[i]; //путь к файлу неймс
        QHash<QString,QString> hash_names = create_hash_names(path_names, number_eas, rfile_log); //создание хешм неймс
        create_hash_all(hash_names,number_eas,rfile_log);
        if(hash_names.constBegin() != hash_names.constEnd())
        {
            pars_names(hash_names, number_eas,cabinets,rfile_log); //парсим строки в хеш и сразу кидаем в базу
            /*------------------------------------------.aks .mks .faw .fbw--------------------------------------------*/
            for(int i = 0; i < 4; i++) //первые 4 select_all
            {
                QString path_group1 = dir_select + number_eas + select_all_EM[i]; //путь к файлу
                QHash<QString,QString> hash_group1 = create_hash_group(path_group1, rfile_log); //создание хеш
                if(hash_group1.begin() != hash_group1.end())
                {
                    pars_group1(opch.value(i),hash_group1,number_eas,rfile_log);
                }
            }
            /*------------------------------------------.em .es .ibr .ite .ivl .ko .kr .sr----------------------*/
            for(int i = 4; i < 12; i++) //следующие 8 select_all
            {
                QString path_group2 = dir_select + number_eas + select_all_EM[i]; //путь к файлу
                QHash<QString,QString> hash_group2 = create_hash_group_equip(path_group2, rfile_log); //создание хеш
                if(hash_group2.begin() != hash_group2.end())
                {
                    pars_group2(opch.value(i),hash_group2,number_eas,rfile_log);
                }
            }
            /*------------------------------------------.te .vl----------------------------------------------------------*/
            for(int i = 12; i < 14; i++)
            {
                QString path_group_te_vl = dir_select + number_eas + select_all_EM[i]; //путь к файлу
                QHash<QString,QString> hash_group_te_vl = create_hash_group_equip(path_group_te_vl, rfile_log); //создание хеш
                if(hash_group_te_vl.begin() != hash_group_te_vl.end())
                {
                    pars_group_te_vl(opch.value(i),hash_group_te_vl,number_eas,cabinets,hash_names,rfile_log);
                }
            }
            /*------------------------------------------.alarms---------------------------------------------------------*/
            QString path_alarms = dir_select + number_eas + select_all_EM[14]; //путь к файлу
            QHash<QString,QString> hash_alarms = create_hash_group(path_alarms, rfile_log); //создание хеш
            if(hash_alarms.begin() != hash_alarms.end())
            {
                pars_alarms(hash_alarms,number_eas,rfile_log);
            }
            /*------------------------------------------.delta---------------------------------------------------------*/
            QString path_delta = dir_select + number_eas + select_all_EM[15]; //путь к файлу
            QHash<QString,QString> hash_delta = create_hash_group(path_delta, rfile_log); //создание хеш
            if(hash_delta.begin() != hash_delta.end())
            {
                pars_delta(hash_delta,number_eas,rfile_log);
            }
            /*------------------------------------------.kl_reg-------------------------------------------------------*/
            QString path_kl_reg = dir_select + number_eas + select_all_EM[16]; //путь к файлу
            QHash<QString,QString> hash_kl_reg = create_hash_group_reg(path_kl_reg,rfile_log); //создание хеш
            if(hash_kl_reg.begin() != hash_kl_reg.end())
            {
                pars_kl_reg(hash_kl_reg,number_eas,cabinets,rfile_log);
            }
            /*------------------------------------------.sr_kr-------------------------------------------------------*/
            QString path_sr_cr = dir_select + number_eas + select_all_EM[17]; //путь к файлу
            QHash<QString,QString> hash_sr_cr = create_hash_group_one(path_sr_cr,rfile_log); //создание хеш
            if(hash_sr_cr.begin() != hash_sr_cr.end())
            {
                pars_sr_kr(hash_sr_cr,number_eas,cabinets,rfile_log);
            }
            /*------------------------------------------.ext_mode-------------------------------------------------------*/
            QString path_ext_mode = dir_select + number_eas + select_all_EM[18]; //путь к файлу
            QHash<QString,QString> hash_ext_mode = create_hash_ext_mode(path_ext_mode,number_eas,rfile_log); //создание хеш
            if(hash_ext_mode.begin() != hash_ext_mode.end())
            {
                pars_ext_mode(hash_ext_mode,number_eas,cabinets,rfile_log);
            }
            /*------------------------------------------.regul-------------------------------------------------------*/
            QString path_regul = dir_select + number_eas + select_all_EM[19]; //путь к файлу
            QHash<QString,QString> hash_regul = create_hash_group_reg(path_regul,rfile_log); //создание хеш
            if(hash_regul.begin() != hash_regul.end())
            {
                pars_regul(hash_regul,number_eas,rfile_log);
            }
            /*------------------------------------------.res_mod-------------------------------------------------------*/
            QString path_res_mod = dir_select + number_eas + select_all_EM[20]; //путь к файлу
            QHash<QString,QString> hash_res_mod = create_hash_group_one(path_res_mod,rfile_log); //создание хеш
            if(hash_res_mod.begin() != hash_res_mod.end())
            {
                pars_res_mod(hash_res_mod,number_eas,rfile_log);
            }
            /*------------------------------------------.vl_ivl-------------------------------------------------------*/
            QString path_vl_ivl = dir_select + number_eas + select_all_EM[21]; //путь к файлу
            QHash<QString,QString> hash_vl_ivl = create_hash_group_one(path_vl_ivl,rfile_log); //создание хеш
            if(hash_vl_ivl.begin() != hash_vl_ivl.end())
            {
                pars_vl_ivl(hash_vl_ivl,number_eas,rfile_log);
            }
        }
    }
    //конец логики
    file_log.open(QIODevice::Append); //открываем новый файл  на запись
    QTextStream in_log(&file_log); //поток в лог
    in_log << "-----------------------------------------------------------------------------------------------------" << '\n'; //для обозначения конца лога
    file_log.close();
    query.finish();
    hash_all.clear();
    emit signal_wrightWidgLog("Сигналы не записанные в базу буду находиться в лог файле:\n"+dir_select_for_log+'-'+"log.txt");
    emit signal_closeWait();
}

void Worker::slot_operationNT(QString dir_select, QSqlDatabase db)
{
    query = QSqlQuery(db); //создаем экземпляр обьекта запроса и привязываем его к БД
    QFile file_log(dir_select+'-'+"log.txt"); //создаем новый файл для хранения log
    QFile &rfile_log = file_log; //создаем ссылку на лог файл для передачи в функцию
    QHash<QString, QString> cabinets = create_hash_cabinets_4(); //создаем hash c кабинетами
    create_tables(rfile_log); //создаем таблицы в бд
    QList<QString> select_names = QDir(dir_select).entryList(QStringList("*.names")); //показывает все файлы в директории c расширением *.names
    QString dir_select_for_log = dir_select;
    dir_select = dir_select.append("\\\\");
    for (int i = 0; i < select_names.size(); i++) //проход по всем файлам неймс
    {
        QString number_eas = select_names[i].left(3); //сохраняем первые три цифры из .names [EAS]
        qDebug() << "number_eas: " << number_eas;
        emit signal_wrightWidgLog("EAS "+number_eas+" обработан");
        QHash<int,QString> opch = create_hash_opch_NT(); //создали хеш opch
        /*------------------------------------------------------.names--------------------------------------------*/
        QString path_names = dir_select + select_names[i]; //путь к файлу неймс
        QHash<QString,QString> hash_names = create_hash_names(path_names, number_eas, rfile_log); //создание хешм неймс
        create_hash_all(hash_names,number_eas,rfile_log);
        if(hash_names.constBegin() != hash_names.constEnd())
        {
            pars_names(hash_names, number_eas,cabinets,rfile_log); //парсим строки в хеш и сразу кидаем в базу

            /*------------------------------------------.aks .mks .ats--------------------------------------------*/
            for(int i = 0; i < 3; i++) //первые 3 select_all
            {
                QString path_group1 = dir_select + number_eas + select_all_NT[i]; //путь к файлу
                QHash<QString,QString> hash_group1 = create_hash_group(path_group1, rfile_log); //создание хеш
                if(hash_group1.begin() != hash_group1.end())
                {
                    pars_group1(opch.value(i),hash_group1,number_eas,rfile_log);
                }
            }
            /*------------------------------------------.esgm.esgs.esgv.ibrn.//iten.ivln//.kom.reg.cru.icum.icus.icuv-------*/

            for(int i = 3; i < 7; i++) //следующие
            {
                QString path_group2 = dir_select + number_eas + select_all_NT[i]; //путь к файлу
                QHash<QString,QString> hash_group2 = create_hash_group_equip(path_group2, rfile_log); //создание хеш
                if(hash_group2.begin() != hash_group2.end())
                {
                    pars_group2(opch.value(i),hash_group2,number_eas,rfile_log);
                }
            }
            /*------------------------------------------iten.ivln.----------------------------------------------*/

            for(int i = 7; i < 9; i++) //следующие
            {
                QString path_group_iten_ivln = dir_select + number_eas + select_all_NT[i]; //путь к файлу
                QHash<QString,QString> hash_iten_ivln = create_hash_group_equip(path_group_iten_ivln, rfile_log); //создание хеш
                if(hash_iten_ivln.begin() != hash_iten_ivln.end())
                {
                    pars_group_te_vl(opch.value(i),hash_iten_ivln,number_eas,cabinets,hash_names,rfile_log);
                }
            }
            /*------------------------------------------kom.reg.cru.icum.icus.icuv---------------------------------*/
            for(int i = 9; i < 15; i++) //следующие
            {
                QString path_group2 = dir_select + number_eas + select_all_NT[i]; //путь к файлу
                QHash<QString,QString> hash_group2 = create_hash_group_equip(path_group2, rfile_log); //создание хеш
                if(hash_group2.begin() != hash_group2.end())
                {
                    pars_group2(opch.value(i),hash_group2,number_eas,rfile_log);
                }
            }

            /*------------------------------------------.alarms---------------------------------------------------------*/
            QString path_alarms = dir_select + number_eas + select_all_NT[15]; //путь к файлу
            QHash<QString,QString> hash_alarms = create_hash_group(path_alarms, rfile_log); //создание хеш
            if(hash_alarms.begin() != hash_alarms.end())
            {
                pars_alarms(hash_alarms,number_eas,rfile_log);
            }
            /*------------------------------------------.delta---------------------------------------------------------*/
            QString path_delta = dir_select + number_eas + select_all_NT[16]; //путь к файлу
            QHash<QString,QString> hash_delta = create_hash_group(path_delta, rfile_log); //создание хеш
            if(hash_delta.begin() != hash_delta.end())
            {
                pars_delta(hash_delta,number_eas,rfile_log);
            }
            /*------------------------------------------.kl_reg-------------------------------------------------------*/
            QString path_kl_reg = dir_select + number_eas + select_all_NT[17]; //путь к файлу
            QHash<QString,QString> hash_kl_reg = create_hash_group_reg(path_kl_reg,rfile_log); //создание хеш
            if(hash_kl_reg.begin() != hash_kl_reg.end())
            {
                pars_kl_reg(hash_kl_reg,number_eas,cabinets,rfile_log);
            }
            /*------------------------------------------.sr_kr-------------------------------------------------------*/
            QString path_sr_cr = dir_select + number_eas + select_all_NT[18]; //путь к файлу
            QHash<QString,QString> hash_sr_cr = create_hash_group_one(path_sr_cr,rfile_log); //создание хеш
            if(hash_sr_cr.begin() != hash_sr_cr.end())
            {
                pars_sr_kr(hash_sr_cr,number_eas,cabinets,rfile_log);
            }

            /*------------------------------------------.regul-------------------------------------------------------*/
            QString path_regul = dir_select + number_eas + select_all_NT[19]; //путь к файлу
            QHash<QString,QString> hash_regul = create_hash_group_reg(path_regul,rfile_log); //создание хеш
            if(hash_regul.begin() != hash_regul.end())
            {
                pars_regul(hash_regul,number_eas,rfile_log);
            }
            /*------------------------------------------.res_mod-------------------------------------------------------*/
            QString path_res_mod = dir_select + number_eas + select_all_NT[20]; //путь к файлу
            QHash<QString,QString> hash_res_mod = create_hash_group_one(path_res_mod,rfile_log); //создание хеш
            if(hash_res_mod.begin() != hash_res_mod.end())
            {
                pars_res_mod(hash_res_mod,number_eas,rfile_log);
            }
            /*------------------------------------------.vl_ivl-------------------------------------------------------*/
            QString path_vl_ivl = dir_select + number_eas + select_all_NT[21]; //путь к файлу
            QHash<QString,QString> hash_vl_ivl = create_hash_group_one(path_vl_ivl,rfile_log); //создание хеш
            if(hash_vl_ivl.begin() != hash_vl_ivl.end())
            {
                pars_vl_ivl(hash_vl_ivl,number_eas,rfile_log);
            }
        }
    }
    //конец логики
    file_log.open(QIODevice::Append); //открываем новый файл  на запись
    QTextStream in_log(&file_log); //поток в лог
    in_log << "-----------------------------------------------------------------------------------------------------" << '\n'; //для обозначения конца лога
    file_log.close();
    query.finish();
    hash_all.clear();
    emit signal_wrightWidgLog("Сигналы не записанные в базу буду находиться в лог файле:\n"+dir_select_for_log+'-'+"log.txt");
    emit signal_closeWait();
}


void MainWindow::on_button_dir_db_clicked() //кнопка выбора бд и подключение драйвера бд
{
    data_base = QFileDialog::getOpenFileName(this,tr("Enter access file"),"C:\\",tr("Access files (*.mdb, *.accdb)")); //Выбираем базу данных в которую будем записывать информацию
    data_base = swap_slesh(data_base); //заменяем слеши на обратные
    ui->label_dir_db->setText(data_base);
    db = QSqlDatabase::addDatabase("QODBC"); //драйвер подключния базы
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ="+data_base); //открываем файл с базой данных в которую будем записывать
    if (db.open())
    {
        qDebug() << "DB open";
    }
    else
    {
        ui->listWidget_log->addItem(db.lastError().text());
        ui->listWidget_log->scrollToBottom();
        qDebug() << db.lastError();
    }
    query = QSqlQuery(db); //создаем экземпляр обьекта запроса и привязываем его к БД
}


void MainWindow::on_button_dir_selects_clicked() //кнопка выбора директории с селектами
{
    dir_select = QFileDialog::getExistingDirectory(this,tr("Open directory"),"C:\\",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks); //Выбираем папку с данными
    dir_select = swap_slesh(dir_select);   //заменяем слеши на обратные
    ui->label_dir_selects->setText(dir_select);
}


void MainWindow::on_button_clear_db_clicked() //кнопка удаления таблиц
{
    del_table("TBL_DOP_INF");
    del_table("TBL_KL_REG");
    del_table("TBL_KLAPAN");
    del_table("TBL_MODUL");
    del_table("TBL_REGUL");
    del_table("TBL_RESERV");
    del_table("TBL_VL_IVL");
}


void MainWindow::on_button_start_clicked() //кнопка старт
{
    if(db.open())
    {
        if(dir_select != nullptr)
        {
            if(ui->radioButton_EM->isChecked() || ui->radioButton_NT->isChecked()) //должен быть выбрант тип тптс
            {
                /*-------------------------------------------------------------------------для ТПТС ЕМ--------------------------------------------------------------*/

                if(ui->radioButton_EM->isChecked())
                {
                    wait->show(); //показываем окно ожидания
                    ui->listWidget_log ->addItem("Старт");
                    ui->listWidget_log->scrollToBottom();
                    //начало логики
                    emit signal_operationEM(dir_select,db);
                }

                /*-------------------------------------------------------------------------для ТПТС НТ--------------------------------------------------------------*/

                if(ui->radioButton_NT->isChecked())
                {
                    wait->show(); //показываем окно ожидания
                    ui->listWidget_log ->addItem("Старт");
                    ui->listWidget_log->scrollToBottom();
                    //начало логики
                    emit signal_operationNT(dir_select,db);
                }
            }
            else
            {
                ui->listWidget_log ->addItem("Выберете тип ТПТС");
                ui->listWidget_log->scrollToBottom();
            }
        }
        else
        {
            ui->listWidget_log ->addItem("Выберете директорию с селектами");
            ui->listWidget_log->scrollToBottom();
            dir_select = nullptr;
        }
    }
    else
    {
        ui->listWidget_log ->addItem("Выберете базу данных в которую нужно перенести данные");
        ui->listWidget_log->scrollToBottom();
    }
}



void MainWindow::on_pushButton_clicked() //кнопка i
{
    open_help->show();
}

