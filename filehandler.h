#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QImage>
#include <QFile>
#include <QMap>
#include <QPixmap>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <QPoint>

struct image_saving_protocol
{
    unsigned int CAMERA_ID;
    unsigned int NUMBER_OF_FRAMES;
    uint64 tmsec;
    cv::Mat frame;
    std::vector<uint8_t> imgbuff;
};

enum camera {left,right};
enum frame_state {next,previos};
Q_DECLARE_METATYPE(image_saving_protocol)

class FileHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileHandler(QObject* parent = nullptr);
    bool Save(image_saving_protocol p);
    QMap<camera,image_saving_protocol> Read(int numFrames);
    void setNameOfFile(const QString& newFileName);
    void matRead(image_saving_protocol& read_protocol, frame_state state);
    void Decode(std::vector<uint8_t> buff, int camera_id);
    void start();
    const std::vector<uint64>& getFrameByteIndex() const;

private:
    QString m_fileName;
    QFile m_file;
    QMap<camera,image_saving_protocol> m_images;
    QVector <image_saving_protocol> m_buff;
    int m_b = qRegisterMetaType<image_saving_protocol>("image_saving_protocol");
    int frameState=qRegisterMetaType<frame_state>("frame_state");
    int position {};
    int current_size {};
    int frames_counter {};
    std::vector<uint64> FrameByteIndex;
    std::vector<std::vector<image_saving_protocol>> image_writing_buffer;
    std::vector<image_saving_protocol> current_stream_buffer;
    void matWrite(const image_saving_protocol& saving_protocol,std::ofstream& fs);
    std::vector<uint64> Data_Indexing();

signals:
    void readImageleft(QPixmap p);
    void readImageRight(QPixmap p);
    void Status(QPoint p);
};

#endif // FILEHANDLER_H
