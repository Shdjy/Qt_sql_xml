#include "widget.h"
#include "ui_widget.h"
#include <QtXml>
#include <QFileDialog>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    //xml写入
    QDomDocument doc;
    //文档对象创建一个标签
    QDomElement root = doc.createElement("root");
    //添加到文档对象
    doc.appendChild(root);

    auto stu = doc.createElement("student");
    root.appendChild(stu);

    //为标签页添加属性
    stu.setAttribute("id","123");
    auto name = doc.createElement("Name");
    auto desc = doc.createElement("Desc");
    stu.appendChild(name);
    stu.appendChild(desc);

    name.appendChild(doc.createTextNode("浩东"));
    desc.appendChild(doc.createTextNode("三好学生"));

    QString filename = QFileDialog::getSaveFileName(this,"保存xml");
    //文件对象
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    //保存文件
    QTextStream outStream(&file);//使用文件流，创建文本流对象
    doc.save(outStream,4);


}

struct Stu
{
    int id;
    QString name;
    QString desc;
};

void Widget::on_pushButton_2_clicked()
{
    //xml内容读取
    QFile file("./testLoad.xml");
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    QVector<Stu> vec;
    //进行读取
    QDomDocument doc;
    //关联文件
    doc.setContent(&file);
    //查找第一个子标签
    auto root = doc.firstChildElement("root");
    //root的第一个子标签
    auto stu = root.firstChildElement("student");

    while(!stu.isNull())
    {
        //进行标签解析
        Stu stuInfo;
        stuInfo.id = stu.attribute("id").toUInt();
        stuInfo.name = stu.firstChildElement("Name").text();
        stuInfo.desc = stu.firstChildElement("Desc").text();

        vec.append(stuInfo);
        //读取下一个hero标签
        stu = stu.nextSiblingElement("student");
    }
    //显示到ui
    QString contents = "";
    for(auto info : vec)
    {
        contents += "Id:" +  QString::number(info.id);
        contents += " Name:" + info.name;
        contents += " Desc:" + info.desc;
        contents += "\n----------------\n";
    }
    ui->textEdit->setText(contents);
}
