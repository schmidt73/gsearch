# gsearch: google search brought to the shell

gsearch is a utility to bring google search to the shell.

## What's the purpose of gsearch?

* It allows users to search from the shell.
* Users can use it to match searches through regex and other filters.
* It can be used to scrape through search results progrmatically.
* Users can combine gsearch with other unix tools for some interesting results (like downloading the first result that matches a certain regular expression with ack and wget). 

gsearch is currently in developement for an alpha release. Once that is done I will work on adding new features such as possibly regex support.

## How to use it?

The best way to learn something is through examples. Here are a few with a decsription of each above.

To search the string "Donald Trump" and print out the first 100 results in table view:

    gsearch -s "Donald Trump" -n 100 

To switch the output to list view:

    gsearch -s "Donald Trump" -n 100 -d list

To only allow searches with the search query in the title:

    gsearch -s "Donald Trump" -n 100 -d list --searchintitle

To restrict search results to a certain country/language (Italy and Italian):

    gsearch -s "Donald Trump" -n 100 -l it -c IT

To restrict search results to the past week:

    gsearch -s "Donald Trump" -n 100 -t w
 
Now those are just simple commands, if we chain them with other unix commands we get some interesting results.

The following downloads the first article on Donald Trump from CNN to your current directory:
    wget $(gsearch -s "Donald Trump site: cnn"" -n 10 --url-only | head -3)

As you can see, we can start chaining commands together to do pretty cool things. Hopefully some of you have better imaginations than I do.

## Installation

To install you need to have the follow dependencies:

* libcurl
* libxml

Installation is pretty easy with the following three commands:

```
./configure
make
make install
```

