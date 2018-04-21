#kivy Modules
import kivy
kivy.require('1.10.0')

from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.slider import Slider


#Python Modules
import sys
from random import randint

#Own Modules
from modules import send

class ColorSlider(Slider):
    def startvalue(self):
        return randint(100,255)

class MainUI(BoxLayout):
    pass

#Main Class
class ESPApp(App):
    def build(self):
        return MainUI()

    def on_pause(self):
        return True

    def on_resume(self):
        return True

    def send_url(self, addr, red, green, blue):
        send.send(addr,r=red,g=green,b=blue)

#Start->
if __name__ == '__main__':
    ESPApp().run()
