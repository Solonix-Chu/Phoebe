#!/bin/bash

# 初始化视频文件夹路径变量
video_folder=""

play_list_tmp=".tmp_rp_ls.txt"

# 捕获 Ctrl+C 信号并执行清理操作
trap 'echo "Script interrupted. Exiting..."; rm $play_list_tmp; exit 1' SIGINT

# 解析命令行参数
while getopts "l:" opt; do
  case $opt in
    l)
      video_folder="$OPTARG"
      ;;
    *)
      echo "Usage: $0 -l video_folder"
      exit 1
      ;;
  esac
done

# 检查是否提供了视频文件夹路径
if [ -z "$video_folder" ]; then
  echo "Error: Missing required argument -l video_folder"
  echo "Usage: $0 -l video_folder"
  exit 1
fi

# 查找所有视频文件，生成随机播放列表
find "$video_folder" -type f \( -iname '*.mp4' -o -iname '*.mkv' -o -iname '*.avi' -o -iname '*.mov' -o -iname '*.flv' \) | shuf > $play_list_tmp

# 循环播放随机列表中的视频文件
while IFS= read -r video
do
    vlc -f "$video"   # 使用 -f 参数使 VLC 播放器全屏播放视频
done < $play_list_tmp

rm $play_list_tmp
