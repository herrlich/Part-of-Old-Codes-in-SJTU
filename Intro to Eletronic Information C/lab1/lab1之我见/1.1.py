def parseURL(content):
    import re
    from BeautifulSoup import BeautifulSoup
    soup=BeautifulSoup(content)
    urlset=set()
    for i in soup.findAll('a',{'href':re.compile('^http*')}):
        urlset.add(i['href'])
    return urlset