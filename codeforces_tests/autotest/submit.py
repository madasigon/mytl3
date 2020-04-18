from selenium import webdriver
from time import sleep
from selenium.common.exceptions import ElementClickInterceptedException, NoSuchElementException
from functools import wraps
from .util import *

@curried(2)
def at(s, f):
    @wraps(f)
    def wrapped_f(self, *args, **kwargs):
        self.get("{}/{}".format(self.root, s.format(*args)))
        return f(self, *args, **kwargs)
    return wrapped_f

class Codeforces(webdriver.Firefox):
    root = "http://codeforces.com"
    
    by_css = webdriver.Firefox.find_element_by_css_selector
    
    def get_(self, from_root):
        return self.get(self.root+from_root)
    
    @at("/enter")
    def login(self, handle, pw):
        self.handle = handle
        self.by_css("#handleOrEmail").send_keys(handle)
        self.by_css("#password").send_keys(pw)
        sleep(1)
        self.by_css("#password").send_keys(u'\ue007')
        sleep(3)
    
    
    @at("/problemset/problem/{}/{}")
    def submit_solution(self, number, letter, path):
        try:
            self.by_css(".close").click()
        except NoSuchElementException:
            pass
        while 1:
            try:
                self.by_css("select[name=\"programTypeId\"] > option[value=\"54\"]").click()
                break
            except ElementClickInterceptedException:
                pass

        self.by_css("input[name=\"sourceFile\"]").send_keys(path)


        self.by_css("input.submit[value=\"Submit\"]").click()

        
        

    
    @at("/problemset/problem/{}/{}")
    def current_status(self, number, letter):
        el = self.find_element_by_xpath("//*[contains(text(), \"Last submissions\")]/..//tbody")
        return " ".join(el.text.split("\n")[1].split()[3:])
    def waiting(self):
        try:
            self.by_css(".verdict-waiting")
            return True
        except NoSuchElementException:
            return False
    
    def sleep_until(self, pred):
        while not pred():
            sleep(0.2)
    
    #def get_last_n_results(self, n):
    #    self.get_("/submissions/{}".format(self.handle))
    #    self.sleep_until(lambda: not self.waiting())
    #return [el.by_css(":nth-child(6)").text for el in self.find_elements_by_css_selector(".highlighted-row")[:n]] #verdict-waiting
    
    def check_n_solutions(self, solutions):
        solutions = list(solutions)
        for (task_id, path) in solutions:
            self.submit_solution(*task_id, path)
        
        sleep(1)
        self.get_("/submissions/{}".format(self.handle))
        self.sleep_until(lambda: not self.waiting())
        sleep(2)
        return [self.current_status(a,b) for ((a, b), _) in solutions]

    @staticmethod
    def which_problem(filename):
        sp = filename.split(".")
        assert(len(sp) >= 3)
        return sp[-3], sp[-2]

    def test_directory(self, dst_path):
        paths = abs_list(dst_path)
        problems = list(map(self.which_problem, filename_list(dst_path)))
        res = self.check_n_solutions(zip(problems, paths))
        return list(zip(paths, res))

    def __init__(self, un, pw):
        from selenium.webdriver.firefox.options import Options

        options = Options()
        options.headless = True
        super(Codeforces, self).__init__(options=options)
        self.login(un, pw)



