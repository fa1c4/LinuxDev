import requests

url = 'http://127.0.0.1:1234/members'
request_body = '''
{
    "name": "Baili5",
    "gender": "Female",
    "powerlevel": "A",
    "powertype": "Forch"
}
'''
print("before post")
print(request_body) 
r = requests.post(url, data=request_body)
print("after post")
print(r.text)
