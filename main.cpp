#include "include/line_detect.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

#define filepath "../src/20191222yokohama.MOV"

int main(int argc, char **argv) {
  cv::VideoCapture video;

  if (argc == 2) {
    video.open(argv[1]);
  } else {
    video.open(filepath);
  }

  if (video.isOpened() == false) {
    return 0;
  }

  cv::VideoWriter writer; // 動画ファイルを書き出すためのオブジェクトを宣言する

  int fourcc = cv::VideoWriter::fourcc(
      'm', 'p', '4', 'v'); // ビデオフォーマットの指定( ISO MPEG-4 / .mp4)
  int width = (int)video.get(cv::CAP_PROP_FRAME_WIDTH); // フレーム横幅を取得
  int height = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT); // フレーム縦幅を取得
  double fps = video.get(cv::CAP_PROP_FPS); // フレームレートを取得

  writer.open("output.mp4", fourcc, fps, cv::Size(width, height));

  cv::Mat image; // 画像を格納するオブジェクトを宣言する
  cv::Mat previous;
  int i = 0;
  while (1) {
    video >> image; // videoからimageへ1フレームを取り込む
    if (image.empty() == true)
      break; // 画像が読み込めなかったとき、無限ループを抜ける
    if (!i) {
      image.copyTo(previous);
    }
    cv::Mat diff;
    cv::absdiff(image, previous, diff);
    cv::imshow("showing", diff); // ウィンドウに動画を表示する
    image.copyTo(previous);
    line_detection(image);
    writer << image; // 画像 image を動画ファイルへ書き出す
    if (cv::waitKey(1) == 'q')
      break; // qを押すと終了
    ++i;
  }
  return 0;
}
