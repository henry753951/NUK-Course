import requests
from bs4 import BeautifulSoup

url = "https://www.cnyes.com/twstock/2330/company/profile"  # 台積電
r = requests.get(url)  # 抓取網頁原始碼
soup = BeautifulSoup(r.text, "html.parser")  # 解析原始碼
try:
    no = soup.find("h2", class_="jsx-162737614").find("span").text  # 股票代號
    stockName = soup.find("h2", class_="jsx-162737614").text  # 股票名稱
    stockName = stockName.replace(no, "")
    category = soup.find(
        "a", class_="jsx-2887475226 button industry-buttons__industry").text  # 產業別
    listed = soup.find(
        "div", class_="jsx-2887475226 button industry-buttons__market").text  # 上市/上櫃
    company_name = soup.find("h3", class_="jsx-63551769").text  # 公司名稱
    capital_account = soup.find_all("div", class_="jsx-4082504959 column isParallel")[
        6].find_all("p", class_="jsx-4082504959")[1].text  # 資本額
    par_value = 10  # 每股面值
    market_cap = soup.find_all(
        "span", class_="jsx-2887475226 value")[8].text  # 目前市值
    issued_share = soup.find_all(
        "span", class_="jsx-2887475226 value")[11].text  # 發行股數
    preferred_stock = soup.find_all("div", class_="jsx-4082504959 column isParallel")[
        12].find_all("p", class_="jsx-4082504959")[1].text  # 特別股
    chairman = soup.find_all(
        "div", class_="jsx-63551769 info")[0].find_all("span")[1].text  # 董事長
    stock = {
        "股票代號": no,
        "股票名稱": stockName,
        "產業別": category,
        "上市/上櫃": listed,
        "公司名稱": company_name,
        "資本額": capital_account,
        "每股面值": par_value,
        "目前市值": market_cap,
        "發行股數": issued_share,
        "特別股": "0" if preferred_stock == "N" else preferred_stock + "股",
        "董事長": chairman
    }

    for key, value in stock.items():
        print(key, ":", value)
except Exception as e:
    print(e)
    pass
