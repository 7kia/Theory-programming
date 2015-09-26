import re, urllib, urllib2, urlparse, os

# Download web-page
url = "http://lenta.ru/"
content = urllib2.urlopen(url).read()

# Find address picture
DataUrls = re.findall('src="(.*?)"', content)
DataUrls = DataUrls + re.findall('href="(.*?)"', content)

# Conversion in absolute address
convertDataUrls = [urlparse.urljoin(url, urlI) for urlI in DataUrls]

os.mkdir('Data')
os.chdir('Data')
# Download data and save in folder Data
for url in convertDataUrls:
    nameFile = url.rsplit('/', 1)[-1]
    if '.' in nameFile:
        try:
            urllib.urlretrieve(url, nameFile)
            # We want that page can open without internet
            content.replace(url, nameFile)
        except:
            print url

# Save converting page
f = open('index.html', 'w')
f.write(content)
f.close()
