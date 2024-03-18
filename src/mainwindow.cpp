#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wait = new wait_time; //инициализируем обьект окна
    wait->setModal(true); //делаем окно модальным,чтобы блокировались остальные окна

}

MainWindow::~MainWindow()
{
    delete ui;
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


void MainWindow::on_button_start_clicked()
{
    wait->show(); //показываем окно ожидания
    pause(2);
    ui->listWidget_log ->addItem("Старт");
    ui->listWidget_log->scrollToBottom();
    //начало логики
    QFile file_log(dir_select+'-'+"log.txt"); //создаем новый файл для хранения log
    QFile &rfile_log = file_log; //создаем ссылку на лог файл для передачи в функцию
    QHash<QString, QString> cabinets = create_hash_cabinets(); //создаем hash c кабинетами
    create_tables(); //создаем таблицы в бд
    QList<QString> select_names = QDir(dir_select).entryList(QStringList("*.names")); //показывает все файлы в директории c расширением *.names
    dir_select = dir_select.append("\\\\");
    for (int i = 0; i < select_names.size(); i++) //проход по всем файлам неймс
    {
        QString number_eas = select_names[i].left(3); //сохраняем первые три цифры из .names [EAS]
        qDebug() << "number_eas: " << number_eas;
        QHash<int,QString> opch = create_hash_opch(); //создали хеш opch
/*------------------------------------------------------.names--------------------------------------------*/
        QString path_names = dir_select + select_names[i]; //путь к файлу неймс
        QHash<QString,QString> hash_names = create_hash_names(path_names, number_eas, rfile_log); //создание хешм неймс
        if(hash_names.constBegin() != hash_names.constEnd())
        {
            pars_names(hash_names, number_eas,cabinets,rfile_log); //парсим строки в хеш и сразу кидаем в базу
            /*------------------------------------------.aks .mks .faw .fbw--------------------------------------------*/
            for(int i = 0; i < 4; i++) //первые 4 select_all
            {
                QString path_group1 = dir_select + number_eas + select_all[i]; //путь к файлу
                QHash<QString,QString> hash_group1 = create_hash_group(path_group1, rfile_log); //создание хеш
                if(hash_group1.begin() != hash_group1.end())
                {
                    pars_group1(opch.value(i),hash_group1,number_eas,rfile_log);
                }
            }
            /*------------------------------------------.em .es .ibr .ite .ivl .ko .kr .sr .te .vl----------------------*/
            for(int i = 4; i < 14; i++) //следующие 10 select_all
            {
                QString path_group2 = dir_select + number_eas + select_all[i]; //путь к файлу
                QHash<QString,QString> hash_group2 = create_hash_group(path_group2, rfile_log); //создание хеш
                if(hash_group2.begin() != hash_group2.end())
                {
                    pars_group2(opch.value(i),hash_group2,number_eas,rfile_log);
                }
            }
            /*------------------------------------------.alarms---------------------------------------------------------*/
                QString path_alarms = dir_select + number_eas + select_all[14]; //путь к файлу
                QHash<QString,QString> hash_alarms = create_hash_group(path_alarms, rfile_log); //создание хеш
                if(hash_alarms.begin() != hash_alarms.end())
                {
                    pars_alarms(hash_alarms,number_eas,rfile_log);
                }
            /*------------------------------------------.delta---------------------------------------------------------*/
                QString path_delta = dir_select + number_eas + select_all[15]; //путь к файлу
                QHash<QString,QString> hash_delta = create_hash_group(path_delta, rfile_log); //создание хеш
                if(hash_delta.begin() != hash_delta.end())
                {
                    pars_delta(hash_delta,number_eas,rfile_log);
                }
            /*------------------------------------------.kl_reg-------------------------------------------------------*/
                QString path_kl_reg = dir_select + number_eas + select_all[16]; //путь к файлу
                QHash<QString,QString> hash_kl_reg = create_hash_group_one(path_kl_reg,rfile_log); //создание хеш
                if(hash_kl_reg.begin() != hash_kl_reg.end())
                {
                    pars_kl_reg(hash_kl_reg,number_eas,cabinets,rfile_log);
                }
            /*------------------------------------------.sr_kr-------------------------------------------------------*/
                QString path_sr_cr = dir_select + number_eas + select_all[17]; //путь к файлу
                QHash<QString,QString> hash_sr_cr = create_hash_group_one(path_sr_cr,rfile_log); //создание хеш
                if(hash_sr_cr.begin() != hash_sr_cr.end())
                {
                    pars_sr_kr(hash_sr_cr,number_eas,cabinets,rfile_log);
                }
            /*------------------------------------------.ext_mode-------------------------------------------------------*/
                QString path_ext_mode = dir_select + number_eas + select_all[18]; //путь к файлу
                QHash<QString,QString> hash_ext_mode = create_hash_ext_mode(path_ext_mode,number_eas,rfile_log); //создание хеш
                if(hash_ext_mode.begin() != hash_ext_mode.end())
                {
                    pars_ext_mode(hash_ext_mode,number_eas,cabinets,rfile_log);
                }
            /*------------------------------------------.regul-------------------------------------------------------*/
                QString path_regul = dir_select + number_eas + select_all[19]; //путь к файлу
                QHash<QString,QString> hash_regul = create_hash_group_one(path_regul,rfile_log); //создание хеш
                if(hash_regul.begin() != hash_regul.end())
                {
                    pars_regul(hash_regul,number_eas,rfile_log);
                }
            /*------------------------------------------.res_mod-------------------------------------------------------*/
                QString path_res_mod = dir_select + number_eas + select_all[20]; //путь к файлу
                QHash<QString,QString> hash_res_mod = create_hash_group_one(path_res_mod,rfile_log); //создание хеш
                if(hash_res_mod.begin() != hash_res_mod.end())
                {
                    pars_res_mod(hash_res_mod,number_eas,rfile_log);
                }
            /*------------------------------------------.vl_ivl-------------------------------------------------------*/
                QString path_vl_ivl = dir_select + number_eas + select_all[21]; //путь к файлу
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
    in_log << "/-----------------------------------------------------------------------------------------------------/" + '\n'; //для обозначения конца лога
    file_log.close();
    ui->listWidget_log ->addItem("Готово");
    ui->listWidget_log->scrollToBottom();
    wait->close(); //закрываем окно ожидания
}

