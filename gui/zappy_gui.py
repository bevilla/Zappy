#!/usr/bin/python2.7

import sys
import subprocess
from PyQt4 import QtGui, QtCore

class ZappyGUI(QtGui.QWidget):
    def __init__(self):
        super(ZappyGUI, self).__init__()
        self.initUI()

    def initUI(self):
        self.easter = ""
        #language dialog
        self.lang = QtGui.QLabel("Choose language", self)
        self.langCombo = QtGui.QComboBox(self)
        self.langCombo.addItems(['ruby', 'python'])
        self.langCombo.move(150, 25)
        self.lang.move(25, 25)

        #IA lvl dialog
        self.lvl = QtGui.QLabel("Choose AI level: ", self)
        self.lvlCombo = QtGui.QComboBox(self)
        self.lvlCombo.addItems(['random', 'easy', 'medium', 'hard'])
        self.lvlCombo.setCurrentIndex(3)
        self.lvlCombo.move(150, 60)
        self.lvl.move(25, 65)

        #GUI dialog
        self.GUI = QtGui.QCheckBox('Launch GUI', self)
        self.GUI.move(25, 90)
        self.GUI.toggle()

        #server dialog
        self.server = QtGui.QCheckBox('Launch server', self)
        self.server.move(25, 120)
        self.server.toggle()

        #map details
        self.sizeDescX = QtGui.QLabel("Map size x: ", self)
        self.sizeDescX.move(25, 165)
        self.sizeX = QtGui.QLineEdit(self)
        self.sizeX.setText("20")
        self.sizeX.move(150, 160)
        self.sizeDescY = QtGui.QLabel("Map size y: ", self)
        self.sizeDescY.move(25, 205)
        self.sizeY = QtGui.QLineEdit(self)
        self.sizeY.setText("20")
        self.sizeY.move(150, 200)

        #mob spinbox
        self.mobDial = QtGui.QLabel("Nb of mob: ", self)
        self.mobDial.move(25, 235)
        self.mobSpinBox = QtGui.QSpinBox(self)
        self.mobSpinBox.setMinimum(0)
        self.mobSpinBox.setMaximum(99)
        self.mobSpinBox.move(150, 230)

        self.btn = QtGui.QPushButton("Run !", self)
        self.btn.move(200, 250)
        self.btn.clicked.connect(self.buttonClicked)

        self.setGeometry(300, 300, 300, 300)
        self.setWindowTitle('Zappy GUI')
        self.show()

    def onActivated(self, text):
        self.lvl.setText(text)
        self.lvl.adjustSize()

    def keyPressEvent(self, e):
        print str(e.text())
        if e.key() == QtCore.Qt.Key_Escape:
            self.close()

    def buttonClicked(self):
        sender = self.sender()
        level = self.lvlCombo.currentText()
        lang = self.langCombo.currentText()
        x = self.sizeX.text()
        y = self.sizeY.text()
        nbMob = self.mobSpinBox.value()
        if self.GUI.isChecked():
            GUI = True
        else:
            GUI = False
        if self.server.isChecked():
            server = True
        else:
            server = False
        print level
        if lang == "python":
            launchPython(GUI, server, level, x, y, nbMob)
        if lang == "ruby":
            launchRuby(GUI, server, level, x, y, nbMob)
        self.close()

def launchPython(GUI, server, level, x, y, nbMob):
    if server == True:
        subprocess.Popen("./zappy_server -n team1 team2 -c 8 -x " + str(x) + " -y " + str(y), shell=True)
    if GUI == True:
        subprocess.Popen("./zappy_graph 127.0.0.1 4242", shell=True)
    subprocess.Popen("cd ai && ./" + str(level) + "_python.sh", shell=True)
    for i in range(int(nbMob)):
        subprocess.Popen("cd ai && ./zappy_ai.py -n team2 -d mob", shell=True)

def launchRuby(GUI, server, level, x, y, nbMob):
    if server == True:
        subprocess.Popen("./zappy_server -n team1 team2 -c 8 -x " + str(x) + " -y " + str(y), shell=True)
    if GUI == True:
        subprocess.Popen("./zappy_graph 127.0.0.1 4242", shell=True)
    subprocess.Popen("cd ai && ./" + str(level) + "_ruby.sh", shell=True)
    for i in range(int(nbMob)):
        subprocess.Popen("cd ai && ./zappy_ai.rb -n team2 -d mob", shell=True)

def main():
    app = QtGui.QApplication(sys.argv)
    gui = ZappyGUI()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()
