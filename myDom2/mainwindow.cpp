#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file("my.xml");
    // 只写方式打开，并清空以前的信息
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return ;

    QDomDocument doc;
    QDomProcessingInstruction instruction;  //添加处理指令
    instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement("书库");
    doc.appendChild(root); //添加根元素

    // 添加第一个book元素及其子元素
    QDomElement book = doc.createElement("图书");
    QDomAttr id = doc.createAttribute("编号");
    QDomElement title = doc.createElement("书名");
    QDomElement author = doc.createElement("作者");
    QDomText text;
    id.setValue("1");
    book.setAttributeNode(id);
    text = doc.createTextNode("《变焦》");
    title.appendChild(text);
    text = doc.createTextNode("伊斯特万·巴克亚伊");
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    // 添加第二个book元素及其子元素
    book = doc.createElement("图书");
    id = doc.createAttribute("编号");
    title = doc.createElement("书名");
    author = doc.createElement("作者");
    id.setValue("2");
    book.setAttributeNode(id);
    text = doc.createTextNode("《图书馆的狮子》");
    title.appendChild(text);
    text = doc.createTextNode("米歇尔·努森");
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);
    QTextStream out(&file);

    doc.save(out,4); // 将文档保存到文件，4为子元素缩进字符数
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//查看全部信息
void MainWindow::on_pushButton_5_clicked()
{
    ui->listWidget->clear(); //先清空显示

    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly)) return ;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();

    //返回根节点及其子节点的元素标记名
    QDomElement docElem = doc.documentElement();  //返回根元素
    QDomNode n = docElem.firstChild();   //返回根节点的第一个子节点
    while(!n.isNull())  //如果节点不为空
    {
        if (n.isElement()) //如果节点是元素
        {
            QDomElement e = n.toElement(); //将其转换为元素
            ui->listWidget->addItem(e.tagName() + e.attribute(tr("编号")));
            QDomNodeList list = e.childNodes();
            for(int i = 0; i < list.length(); i++)
            {
                QDomNode node = list.at(i);
                if(node.isElement())
                    ui->listWidget->addItem("   " + node.toElement().tagName() + " : " + node.toElement().text());
            }
        }
        n = n.nextSibling();  //下一个兄弟节点
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    //我们先清空显示，然后显示“无法添加！”
    ui->listWidget->clear();
    ui->listWidget->addItem(tr("无法添加!"));
    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly))
        return;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    QDomElement root = doc.documentElement();
    QDomElement book = doc.createElement("图书");
    QDomAttr id = doc.createAttribute("编号");
    QDomElement title = doc.createElement("书名");
    QDomElement author = doc.createElement("作者");
    QDomText text;

    // 我们获得了最后一个孩子结点的编号，然后加1，便是新的编号
    QString num = root.lastChild().toElement().attribute("编号");
    int count = num.toInt() + 1;
    id.setValue(QString::number(count));
    book.setAttributeNode(id);

    text = doc.createTextNode(ui->lineEdit_title->text());
    title.appendChild(text);

    text = doc.createTextNode(ui->lineEdit_author->text());
    author.appendChild(text);

    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return ;
    QTextStream out(&file);
    doc.save(out,4);   //将文档保存到文件，4为子元素缩进字符数
    file.close();
    ui->listWidget->clear(); //最后更改显示为“添加成功！”
    ui->listWidget->addItem(tr("添加成功！"));
}

void MainWindow::doXml(const QString operate)
{
    ui->listWidget->clear();
    ui->listWidget->addItem(tr("没有找到相关内容！"));
    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly))
        return ;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();

    QDomNodeList list = doc.elementsByTagName("图书");
    // 以标签名进行查找
    for(int i = 0; i < list.length(); i++)
    {
        QDomElement e = list.at(i).toElement();

        // 如果元素的“编号”属性值与我们所查的相同
        if(e.attribute("编号") == ui->lineEdit_id->text())
        {
            // 如果元素的“编号”属性值与我们所查的相同
            if(operate == "delete")  //如果是删除操作
            {
                QDomElement root = doc.documentElement(); //取出根节点
                root.removeChild(list.at(i));  //从根节点上删除该节点
                QFile file("my.xml");     //保存更改
                if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    return ;
                QTextStream out(&file);
                doc.save(out,4);
                file.close();
                ui->listWidget->clear();
                ui->listWidget->addItem(tr("删除成功！"));
            }

            else if(operate == "update")  //如果是更新操作
            {
                QDomNodeList child = list.at(i).childNodes();
                //找到它的所有子节点，就是“书名”和“作者”
                child.at(0).toElement().firstChild().setNodeValue(ui->lineEdit_title->text());
                //将它子节点的首个子节点（就是文本节点）的内容更新
                child.at(1).toElement().firstChild().setNodeValue(ui->lineEdit_author->text());
                QFile file("my.xml");     //保存更改
                if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    return ;
                QTextStream out(&file);
                doc.save(out,4);   //保存文档，4为子元素缩进字符数
                file.close();
                ui->listWidget->clear();
                ui->listWidget->addItem(tr("更新成功！"));
            }

            else if(operate == "find")  //如果是查找操作
            {
                ui->listWidget->clear();
                ui->listWidget->addItem(e.tagName() + e.attribute(tr("编号")));
                QDomNodeList list = e.childNodes();
                for(int i = 0 ; i < list.length(); i++)
                {
                    {
                        QDomNode node = list.at(i);
                        if(node.isElement())
                            ui->listWidget->addItem("   " + node.toElement().tagName() + " : " + node.toElement().text());
                    }
                }
            }
        }
    }
}

// 查找
void MainWindow::on_pushButton_clicked()
{
    doXml("find");
}

// 删除
void MainWindow::on_pushButton_2_clicked()
{
    doXml("delete");
}

// 更新
void MainWindow::on_pushButton_3_clicked()
{
    doXml("update");
}
