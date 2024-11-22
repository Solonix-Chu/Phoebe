import json
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QTextEdit, QPushButton, QLabel


class BLEMessageSimulator(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("BLE Message Simulator")

        # 创建布局
        layout = QVBoxLayout()

        # 创建文本框
        self.text_box = QTextEdit(self)
        self.text_box.setPlaceholderText("Enter your message here...")
        layout.addWidget(self.text_box)

        # 创建按钮
        self.button = QPushButton("Send", self)
        self.button.clicked.connect(self.on_button_click)
        layout.addWidget(self.button)

        # 创建标签显示结果
        self.result_label = QLabel(self)
        layout.addWidget(self.result_label)

        # 设置窗口布局
        self.setLayout(layout)

    def on_button_click(self):
        message = self.text_box.toPlainText()

        try:
            # 尝试解析文本为 JSON
            json_data = json.loads(message)
            # 压缩 JSON
            compressed_json = json.dumps(json_data, separators=(',', ':'))
            print(compressed_json)  # 打印压缩后的 JSON
            self.result_label.setText("Valid JSON compressed and printed.")
            self.result_label.setStyleSheet("color: green;")  # 设置文本颜色为绿色
        except json.JSONDecodeError:
            self.result_label.setText("Invalid JSON.")
            self.result_label.setStyleSheet("color: red;")  # 设置文本颜色为红色


# 创建应用程序
app = QApplication([])

# 创建窗口
window = BLEMessageSimulator()
window.resize(400, 250)
window.show()

# 运行主循环
app.exec_()
