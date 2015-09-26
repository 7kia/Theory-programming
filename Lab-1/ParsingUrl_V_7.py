import re, urllib, urllib2, urlparse, os

# Download web-page
def findUrlWithText(url, text):
    if not (url in usedUrls) and text:
        usedUrls.append(url)
        content = urllib2.urlopen(url).read()

        #print url# I want know current url

        # Find address data
        DataUrls = re.findall('href="(.*?)"', content)

        # Conversion in absolute address
        convertDataUrls = [urlparse.urljoin(url, urlI) for urlI in DataUrls]

        # if text is finded then download
        if text in content:
            print 'FIND!!!'
            download(url)

        for urlList in convertDataUrls:
            nameFile = urlList.rsplit('/', 1)[-1]
            if '.htm' in nameFile or '.html' in nameFile:
                findUrlWithText(urlList, text)

def download(url):
    #if not (url in usedUrls):
    usedUrls.append(url)

    contentDownload = urllib2.urlopen(url).read()

    # Find address data
    DataUrls = re.findall('src="(.*?)"', contentDownload)
    DataUrls = DataUrls + re.findall('href="(.*?)"', contentDownload)

    # Conversion in absolute address
    convertDataUrls = [urlparse.urljoin(url, urlI) for urlI in DataUrls]

    # Define name directory
    nameDirectory =  re.findall('<title>(.*?)</title>', contentDownload)
    nameDirectory = nameDirectory[0]

    #os.mkdir(nameDirectory)
    os.mkdir(nameDirectory)
    os.chdir(nameDirectory)

    # Download data and save in folder Data
    lenData = len(DataUrls)
    urlId = 0
    while urlId < lenData:
        url = DataUrls[urlId]
        nameFile = url.rsplit('/', 1)[-1]
        pathFile = nameDirectory + '/'
        try:
            if '.' in nameFile:
                urllib.urlretrieve(convertDataUrls[urlId], nameFile)
                # We want that page can open without internet
                print url, pathFile + nameFile
                contentDownload.replace(url, pathFile + nameFile)
        except:
            print 'error url:'
            print pathFile
        urlId += 1
        if not (urlId < lenData):
            # Back on one directory
            currentPath = os.getcwd()
            buffPath = currentPath.split('\\')[:-1]

            # \ will delete by split and back
            buffPath[0] += '\\'
            for element in buffPath[1:]:
                buffPath[0] += element + '\\'

            os.chdir(buffPath[0])

            # Save converting page
            print contentDownload
            f = open(nameDirectory + '.html', 'w')
            f.write(contentDownload)
            f.close()

###########################################
### \/              Main             \/ ###

url = "https://www.python.org/"
text = 'Software'

usedUrls = []
findUrlWithText(url, text)
