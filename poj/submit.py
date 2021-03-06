#!/usr/bin/env python

# -*- coding: utf-8 -*-
import re
import sys
import logging
from time import sleep
import urllib,urllib2,cookielib
from BeautifulSoup import BeautifulSoup

class POJ:
    URL_HOME = 'http://poj.org/'
    URL_LOGIN = URL_HOME + 'login?'
    URL_SUBMIT = URL_HOME + 'submit?'
    URL_STATUS = URL_HOME + 'status?'
    #....
    INFO =['RunID','User','Problem','Result','Memory','Time','Language','Code Length','Submit Time']
    #..
    LANGUAGE = {
            'G++':'0',
            'GCC':'1',
            'JAVA':'2',
            'PASCAL':'3',
            'C++':'4',
            'C':'5',
            'FORTRAN':'6',
            }

    def __init__(self, user_id, password):
        self.user_id = user_id
        self.password = password
        cj = cookielib.LWPCookieJar()
        self.opener =urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
        urllib2.install_opener(self.opener)

    def login(self):
        data = dict(
                user_id1 = self.user_id,
                password1 = self.password,
                B1 = 'login',
                url = '.')
        postdata = urllib.urlencode(data)
        try:
            req = urllib2.Request(POJ.URL_LOGIN,postdata)
            res = self.opener.open(POJ.URL_LOGIN,postdata).read()
            if res.find('loginlog')>0:
                logging.info("login successful!")
                return True
            else:
                logging.error('login failed')
                return False
        except:
            logging.error('login failed')
            return False

    def submit(self,pid,language,src):
        submit_data = dict(
                problem_id = pid,
                language = POJ.LANGUAGE[language.upper()],
                source = src,
                submit = 'Submit',)
        postdata2 = urllib.urlencode(submit_data)
        try:
            req2 = urllib2.Request(POJ.URL_SUBMIT,data = postdata2)
            res = self.opener.open(POJ.URL_SUBMIT,postdata2).read()
            logging.info('submit successful')
            return True
        except:
            logging.error('submit error')
            return False

    def result(self,user_id):
        url = POJ.URL_STATUS + urllib.urlencode({'user_id':user_id})
        page = urllib2.urlopen(url)
        soup = BeautifulSoup(page)
        table = soup.findAll('table',{'class':'a'}) #....
        pattern = re.compile(r'>[-+: \w]*<')  #............
        result = pattern.findall(str(table))
        #..........
        wait = ['Running & Judging','Compiling','Waiting']
        for i in range(3):
            if result[32][1:-1]==wait[i] or result[32][1:-1] == '':
                logging.info(result[32])
#                sleep(1)
                return False
        #.....result......
        num = [21,24,28,32,35,37,40,43,45]
        for i in range(9):
            print POJ.INFO[i],':',result[num[i]][1:-1]
        return True


if __name__=='__main__':
    #..logging....
    FORMAT = '----%(message)s----'
    logging.basicConfig(level=logging.INFO,format = FORMAT)
    if len(sys.argv) > 1: #.......
        user_id = 'faircoala'
        lang = 'g++'
        pwd = 'poj@ict'
        pid, src, = sys.argv[1:]
        src = open(src,'r').read()
    else:  #..
        user_id = 'faircoala'
        pwd = 'poj@ict'
        pid = 1000
        lang = 'gcc'
        src = '''
        #include<stdio.h>
        int main()
        {
            int a,b;
            scanf("%d%d",&a,&b);
            printf("%d",a+b);
            return 0;
        }
        '''
    logging.info('connecting to server')
    poj = POJ(user_id,pwd)
    if poj.login():
        logging.info("submiting")
        if poj.submit(pid,lang,src):
            logging.info('getting result')
            status = poj.result(user_id)
            while status!=True:  #.......
                status = poj.result(user_id)
