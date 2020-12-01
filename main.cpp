#include <iostream>
#include <opencv2/opencv.hpp>

#define filepath "../src/20191222yokohama.MOV"

int main()
{
    cv::VideoCapture video;
    video.open(filepath);

    if (video.isOpened() == false) {
        return 0;
    }
    cv::VideoWriter writer;     // 動画ファイルを書き出すためのオブジェクトを宣言する
    int width, height, fourcc;  // 作成する動画ファイルの設定
    double fps;
    fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');  // ビデオフォーマットの指定( ISO MPEG-4 / .mp4)
    width = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);      // フレーム横幅を取得
    height = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);    // フレーム縦幅を取得
    fps = video.get(cv::CAP_PROP_FPS);                     // フレームレートを取得

    writer.open("output.mp4", fourcc, fps, cv::Size(width, height));
    cv::Mat image;  // 画像を格納するオブジェクトを宣言する
    while (1) {
        video >> image;  // videoからimageへ1フレームを取り込む
        if (image.empty() == true)
            break;                     // 画像が読み込めなかったとき、無限ループを抜ける
        cv::imshow("showing", image);  // ウィンドウに動画を表示する
        writer << image;               // 画像 image を動画ファイルへ書き出す
        if (cv::waitKey(1) == 'q')
            break;  //qを押すと終了
    }
    return 0;
}
