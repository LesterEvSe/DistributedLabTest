# Website analytics
You are a developer of a website that sells some products, like Amazon.
The marketing department asked you to collect some analytics.
You have two CSV files with data about visiting pages with products.
Each file represents some day. Your task is to find all the users that:  

- Visited some pages on both days
- On the second day visited the page that hadn’t been visited by this user on the first day

## Task
- Create a console app that finds all the users according to the description
- As input, you will have two CSV files with such structure: user_id,product_id,timestamp. Each file represents a separate day. Duplicates are possible, which means the user may visit the same page.
- As output, you just log into the console with all user IDs
- Try to make the algorithm efficient in terms of both storage and execution time
- Explain why your solution is efficient, and possibly classify your solution in big O notation (README.md)

## Result
- Publish code on github
- In README.md place all the explanations about how to run code and additional info.
