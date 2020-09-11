from cs50 import SQL

from helpers import lookup

db = SQL("sqlite:///finance.db")
symbol = "USD"
stock_to_sell = db.execute("SELECT * FROM stocks WHERE symbol = :symbol", symbol=symbol)

user =  db.execute("SELECT * FROM users WHERE id=1")

# Query API for current price
current_stock = lookup(symbol)
price = {"symbol": symbol, "price": current_stock["price"]}

user_cash = user[0]["cash"]

shares_left = 4 - 1
total_sale = 1 * price["price"]
total_cash = total_sale + user_cash
total = float(shares_left * price["price"])

print(shares_left)
print(total_sale)
print(total_cash)
print(total)