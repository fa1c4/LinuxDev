import requests

url = 'http://192.168.129.128:1234/members'
request_params = {'name': 'Baili', 'gender': 'male'}
r = requests.get(url, params=request_params)

print(r.text)

'''
or 
hostname -I # 192.168.129.128
you can access http://192.168.129.128:1234/members?name=Baili&gender=male
to see the effect of mWebServiceGetParam.elf
'''