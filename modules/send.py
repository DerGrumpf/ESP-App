from __future__ import print_function
import urllib

from kivy.network.urlrequest import UrlRequest
from kivy.uix.popup import Popup
from kivy.uix.button import Button



#Handle Client
def handle_success(request, result):
    print(result)

def handle_redirect(request, result):
    print(result)

def handle_failure(request, result):
    print(result)
    feed(title='Failure Connection',text=result)

def handle_error(request, error):
    print(error)
    feed(title='Error Connection',text=error)

#Popupfeed
def feed(title='0',text='Close'):
    content = Button(text=text)
    popup = Popup(title=title, content=content, auto_dismiss=False)
    content.bind(on_press=popup.dismiss)
    popup.open()

#Send URL with GET
def send(addr,r='0', g='0', b='0'):
    #Build HTTP-address
    params = urllib.urlencode(
             {'RED': r,
              'GREEN': g,
              'BLUE': b})
              
    addr = 'http://' + addr + '/genericArgs?'

    req = UrlRequest(addr,
                    on_success=handle_success,
                    on_redirect=handle_redirect,
                    on_failure=handle_failure,
                    on_error=handle_error,
                    on_progress=None,
                    req_body=params,
                    req_headers=None,
                    chunk_size=8192,
                    timeout=None,
                    method='GET',
                    decode=True,
                    debug=False,
                    file_path=None,
                    ca_file=None,
                    verify=False,
                    proxy_host=None,
                    proxy_port=None,
                    proxy_headers=None)

    #Debugg Options
    print(req)
    print(params)
