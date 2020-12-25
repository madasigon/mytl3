from selenium import webdriver
from selenium.webdriver.firefox.options import Options
from time import sleep
from selenium.common.exceptions import ElementClickInterceptedException, NoSuchElementException
from functools import wraps
from .util import *
import getpass
import subprocess
from threading import Thread, Event


class CustomDict(dict):

    def __str__(self):
        return "\n".join(k + ": " + v for k,v in self.items())

    def __setitem__(self, k, v):
        super().__setitem__(k, v)
        print("===================")
        print(self)

class Codeforces():
    def submit_solution(self, problem, path, d, sent_event):
        d[path] = "Submitting"
        command = "cf submit -f "+path+ " " + problem
        p = subprocess.Popen(command, stdout=subprocess.PIPE)
        
        while 1:
            sent = True
            l = p.stdout.readline()
            if l.find(b"status") != -1:
                d[path] = l.split(b"status: ")[1][:-1].decode()
            elif l.find(b"You have submitted exactly the same code before") != -1:
                d[path] = "Resubmission"
            elif l.find(b"Submit failed") != -1:
                d[path] = "Failed to submit."
            elif l.find(b"Too many requests") > -1:
                d[path] = "Too many requests."
            else:
                sent = False

            if sent:
                pass
                sent_event.set()
            
            if not l:
                return

    
    def check_n_solutions(self, solutions):
        d = CustomDict({solution: "Waiting to upload" for solution in solutions})
        print(d)

        tasks = []
        import time
        for path in solutions:
            sent = Event()
            tasks.append(Thread(target=self.submit_solution, args=(self.which_problem(path), path, d, sent)))
            tasks[-1].daemon = True
            tasks[-1].start()
            sent.wait()

        for t in tasks:
            t.join()
        return d

    @staticmethod
    def which_problem(filename):
        return filename.split(".")[-2]



