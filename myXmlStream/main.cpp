#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    QFile file("../myXmlStream/my.xml");
//    if (!file.open(QFile::ReadOnly | QFile::Text))
//    {
//        qDebug()<<"Error: cannot open file";
//        return 1;
//    }

//    QXmlStreamReader reader;

//    // 设置文件，这时会将流设置为初始状态
//    reader.setDevice(&file);

//    // 如果没有读到文档结尾，而且没有出现错误
//    while (!reader.atEnd()) {
//        // 读取下一个记号，它返回记号的类型
//        QXmlStreamReader::TokenType type = reader.readNext();

//        // 下面便根据记号的类型来进行不同的输出
//        if (type == QXmlStreamReader::StartDocument)
//            qDebug() << "=>1<=" << reader.documentEncoding() << reader.documentVersion();
//        if (type == QXmlStreamReader::StartElement)
//        {
//            qDebug() << "=>2<=" << "<" << reader.name() << ">";
//            if (reader.attributes().hasAttribute("id"))
//                    qDebug() << "=>3<=" << reader.attributes().value("id");
//        }
//        if (type == QXmlStreamReader::EndElement)
//                 qDebug() << "=>4<=" << "";
//        if (type == QXmlStreamReader::Characters && !reader.isWhitespace())
//            qDebug() << "=>5<=" << reader.text();
//    }

//    // 如果读取过程中出现错误，那么输出错误信息
//    if (reader.hasError()) {
//        qDebug() << "error: " << reader.errorString();
//    }

//    file.close();

    QFile file("../myXmlStream/my2.xml");
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Error: cannot open file";
        return 1;
    }

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("code");
    stream.writeAttribute("href", "https://github.com/");
    stream.writeTextElement("title", "同性交友");
    stream.writeEndElement();
    stream.writeEndDocument();

    file.close();

    qDebug() << "write finished!";

    return a.exec();
}
