import requests
from bs4 import BeautifulSoup
import time
import random
for i in range(1101, 1131):
    url = "https://www.cnyes.com/twstock/"+str(i)+"/"  # 1101~1130
    web = requests.get(url)  # 抓取request
    soup = BeautifulSoup(web.text, "html.parser")  # 解析原始碼

    try:
        no = soup.find("h2", class_="jsx-162737614").find("span").text
        stockName = soup.find("h2", class_="jsx-162737614").text
        stockName = stockName.replace(no, "")  # 保留股票名稱
        close = soup.find("div", class_="jsx-162737614 price").find("h3").text
        print(no, " ", stockName, " ", close)
    except:
        continue
    time.sleep(random.random())  # 隨機暫停 0~1秒
