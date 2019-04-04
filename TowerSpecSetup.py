import kivy
import os
from kivy.app import App
from kivy.uix.gridlayout import GridLayout
from kivy.uix.label import Label
from kivy.lang import Builder
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button
from kivy.uix.checkbox import CheckBox
from kivy.core.window import Window
from kivy.properties import ObjectProperty
from subprocess import check_output
import subprocess

Builder.load_string('''
<MenuScreen>:
    isCube: isCube.active
    isCuboid: isCuboid.active
    isTetra: isTetra.active
    isTetra90: isTetraN.active
    cubeVal: cubeVal.text
    cuboidValX: cubiodValX.text
    cubiodValY: cubiodValY.text
    cubiodValZ: cubiodValZ.text
    tetraValLenght: tetraValL.text
    tetraValHeight: tetraValH.text
    tetra90ValLength: tetraNValL.text
    tetra90ValHeight: tetraNValH.text

    GridLayout:
        cols: 2
        rows: 8
        Label:
            text: 'Building Block'
        GridLayout:
            cols: 4
            rows: 2
            CheckBox:
                id: isCube
            CheckBox:
                id: isCuboid
            CheckBox:
                id: isTetra
            CheckBox:
                id: isTetraN

            Label:
                text: 'Cube'
            Label:
                text: 'Cuboid'
            Label:
                text: 'Tetra'
            Label:
                text: 'Tetra90'


        Label:
            text: 'Cube'
        TextInput:
            id: cubeVal
            multiline: False

        Label:
            text: 'Cuboid'
        GridLayout:
            cols: 3
            rows: 0
            TextInput:
                id: cubiodValX
                multiline: False
            TextInput:
                id: cubiodValY
                multiline: False
            TextInput:
                id: cubiodValZ
                multiline: False

        Label:
            text: 'Tetra'
        GridLayout:
            cols: 2
            rows: 0
            TextInput:
                id: tetraValL
                multiline: False
            TextInput:
                id: tetraValH
                multiline: False

        Label:
            text: 'Tetra90'
        GridLayout:
            cols: 2
            rows: 0
            TextInput:
                id: tetraNValL
                multiline: False
            TextInput:
                id: tetraNValH
                multiline: False

        Button:
            text: 'Change Base Text >>>'
            on_press:
                root.manager.transition.direction = 'left'
                root.manager.current = 'base_text'
        Button:
            text: 'Change Character Map >>>'
            on_press:
                root.manager.transition.direction = 'left'
                root.manager.current = 'char_map'

        GridLayout:
            cols: 2
            rows: 0
            GridLayout:
                cols:0
                rows:2
                Button:
                    text: 'Save Settings'
                    on_press: root.saveSettings()
                Button:
                    text: 'Open Latest'
                    on_press: root.openLatestSettings()
        GridLayout:
            cols: 2
            rows: 0
            Button:
                text: 'Build!'
                on_press: root.startBuild()
            Button:
                text: 'Run!'
                on_press: root.runTower()

<BaseTextScreen>:
    Label:
        text: 'Functionality is coming!'
    Button:
        text: '<<< Go Back'
        on_press:
            root.manager.transition.direction = 'right'
            root.manager.current = 'menu'

<CharMapScreen>:
    Label:
        text: 'Functionality is coming!'
    Button:
        text: '<<< Go Back'
        on_press:
            root.manager.transition.direction = 'right'
            root.manager.current = 'menu'
''')

class BaseTextScreen(Screen):
    pass

class CharMapScreen(Screen):
    pass

class MenuScreen(Screen):
    isCube = ObjectProperty(None)
    isCuboid = ObjectProperty(None)
    isTetra = ObjectProperty(None)
    isTetra90 = ObjectProperty(None)
    cubeVal = ObjectProperty(None)
    cuboidValX = ObjectProperty(None)
    cubiodValY = ObjectProperty(None)
    cubiodValZ = ObjectProperty(None)
    tetraValLenght = ObjectProperty(None)
    tetraValHeight = ObjectProperty(None)
    tetra90ValLength = ObjectProperty(None)
    tetra90ValHeight = ObjectProperty(None)

    def openLatestSettings(self):
        print('---------------------')
        print('Latest Tower Settings Opened')
        subprocess.Popen('run\\inputs\\towerspecs.txt', shell=True)
        print('---------------------')
        #os.system('run\\inputs\\towerspecs.txt')

    def saveSettings(self):
        fob = open('run\\inputs\\towerspecs.txt', 'w')

        buildingBlockChoose = [0,0,0,0]
        if (self.isCube):
            buildingBlockChoose[0] = 1
        if (self.isCuboid):
            buildingBlockChoose[1] = 1
        if (self.isTetra):
            buildingBlockChoose[2] = 1
        if (self.isTetra90):
            buildingBlockChoose[3] = 1

        fob.write(str(buildingBlockChoose[0]) + ' ' +
                  str(buildingBlockChoose[1]) + ' ' +
                  str(buildingBlockChoose[2]) + ' ' +
                  str(buildingBlockChoose[3]) + '\n')

        #TODO: fucking ugly (place 0 if size is not specified)
        if(self.cubeVal):
            fob.write(str(self.cubeVal) + '\n')
        else:
            fob.write('0' + '\n')

        if(self.cuboidValX):
            fob.write(str(self.cuboidValX) + ' ')
        else:
            fob.write('0' + ' ')
        if(self.cubiodValY):
            fob.write(str(self.cubiodValY) + ' ')
        else:
            fob.write('0' + ' ')
        if(self.cubiodValZ):
            fob.write(str(self.cubiodValZ) + '\n')
        else:
            fob.write('0' + '\n')

        if(self.tetraValLenght):
            fob.write(str(self.tetraValLenght) + ' ')
        else:
            fob.write('0' + ' ')
        if(self.tetraValHeight):
            fob.write(str(self.tetraValHeight) + '\n')
        else:
            fob.write('0' + '\n')

        if(self.tetra90ValLength):
            fob.write(str(self.tetra90ValLength) + ' ')
        else:
            fob.write('0' + ' ')
        if(self.tetra90ValHeight):
            fob.write(str(self.tetra90ValHeight))
        else:
            fob.write('0')

        fob.close()

        print('---------------------')
        print('Tower Settings Saved To File!')
        print('---------------------')



    def startBuild(self):
            print('---------------------')
            print('Build started!')
            subprocess.Popen('g++ texwer.cc InputProcessor.cc TowerBuilder.cc -o texwer.exe', shell=True)
            print('---------------------')

    def runTower(self):
        print('---------------------')
        subprocess.Popen('texwer.exe', shell=True)
        print('---------------------')

     #TODO: add functionality: open latest generated STL


sm = ScreenManager()
sm.add_widget(MenuScreen(name='menu'))
sm.add_widget(BaseTextScreen(name='base_text'))
sm.add_widget(CharMapScreen(name='char_map'))

class TestApp(App):
    def build(self):
        return sm

if __name__ == '__main__':
    TestApp().run()
