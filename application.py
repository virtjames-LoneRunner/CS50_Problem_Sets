import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Determine the current user
    user_id = session["user_id"]
    rows = db.execute("SELECT username, cash FROM users WHERE id = ?", user_id)
    user = rows[0]["username"]
    user_cash = rows[0]["cash"]

    # Determine the stocks owned by the user
    # For retriving every detail
    purchased_stocks = db.execute("SELECT * FROM stocks WHERE user_id = :user_id", user_id = user_id)

    total_amount_from_stocks = 0.00

    # Determine the total amount
    for price in purchased_stocks:
        total_amount_from_stocks += float(price["total"])
    
    total = total_amount_from_stocks + user_cash

    # Format to USD
    for x in range(len(purchased_stocks)):
        purchased_stocks[x]["price"] = usd(purchased_stocks[x]["price"])
        purchased_stocks[x]["total"] = usd(purchased_stocks[x]["total"])

    return render_template("index.html", owned_stocks = purchased_stocks, 
                            cash = usd(user_cash), total = usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    
    # Determine the current user
    user_id = session["user_id"]
    rows = db.execute("SELECT username, cash FROM users WHERE id = :user_id", user_id = user_id)
    user = rows[0]["username"]
    user_cash = rows[0]["cash"]
    
    # User sent a symbol
    if request.method == "POST":

        # Ensure that symbol input field is not empty
        if not request.form.get("symbol"):
            return apology("you must provide stock symbol", 403)
        
        # Ensure that shares input field is not empty
        if not request.form.get("shares"):
            return apology("you must input the number of shares", 403)

        # Ensure that the user entered a non-zero non-negative integer 
        if int(request.form.get("shares")) < 1:
            return apology("you must enter a non-negative and non-zero integer", 403)

        # Look-up the stock
        symbol = request.form.get("symbol")
        stock = lookup(symbol)

        # Check if lookup returned any value
        if stock == None:
            return apology("symbol does not match any stock on record", 403)

        # Define variables for convinience
        stock_price = stock["price"]
        number_of_shares = request.form.get("shares")
        total_amount = stock_price * float(number_of_shares)

        # Ensure that the user can afford to pay the stock
        if total_amount <= user_cash:
            
            # Reassign the user's cash after purchase
            user_cash = user_cash - total_amount

            try:
                stock_shares_in_database = db.execute("""SELECT shares, total FROM stocks 
                                                       WHERE (user_id = :user_id, symbol = :symbol)""", 
                                                       user_id = user_id, symbol = stock["symbol"])
                
                
                shares = stock_shares_in_database["shares"] + number_of_shares
                total = stock_shares_in_database["total"] + total_amount

                # Update the user's shares
                db.execute("UPDATE stocks SET shares = :shares, total = :total WHERE user_id = :user_id", 
                            shares = shares, total = total, user_id = user_id)

                # Update the user's cash to reflect the recent purchase
                db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", 
                            cash = user_cash, user_id = user_id)

            except:
                # Insert the details for the purchased stock into the table "stocks"
                db.execute("""INSERT INTO stocks (user_id, symbol, name, shares, price, total) 
                            VALUES (:user_id, :symbol, :name, :shares, :price, :total)""",
                            user_id = user_id, symbol = stock["symbol"], name = stock["name"], 
                            shares = number_of_shares,
                            price = stock["price"], total = total_amount)
                
                # Update the user's cash to reflect the recent purchase
                db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", 
                            cash = user_cash, user_id = user_id)

            
            # Update history database
            db.execute("""INSERT INTO history (user_id, symbol, shares, price, date_time) 
                        VALUES (:user_id, :symbol, :shares, :price, :date_time)""", 
                        user_id = user_id, symbol = stock["symbol"], shares = number_of_shares, price = stock["price"], date_time = datetime.now())

            return redirect("/")
        
        else:
            return apology("you do not have enough money to buy these stocks", 403)

    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Query database for user's transaction history
    transactions = db.execute("SELECT * FROM history WHERE user_id = :user_id", 
                               user_id = session["user_id"])

    # Format to USD
    for x in range(len(transactions)):
        transactions[x]["price"] = usd(transactions[x]["price"])

    return render_template("history.html", stocks = transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User sent a POST request sending the symbol
    if request.method == "POST":

        # Ensure that the user entered a symbol
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 403)

        # Look-up the stock
        symbol = request.form.get("symbol")
        quote_data = lookup(symbol)
        
        # Check if lookup returned any value
        if quote_data == None:
            return apology("symbol does not match any stock on record", 403)

        return render_template("quote_values.html", name = quote_data["name"], price = usd(quote_data["price"]), symbol = quote_data["symbol"])

    else:
        return render_template("quote_submit.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match, 403")

        # Query database to check if username already exists
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username doesn't already exists
        if len(rows) == 1:
            return apology("username already exists", 403)

        else:
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)", 
                        username = request.form.get("username"), 
                        password = generate_password_hash(request.form.get("password")))

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """Change password"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure current password was submitted
        if not request.form.get("current"):
            return apology("must provide current password", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must new provide password", 403)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match, 403")

        # Query database to check if username already exists
        rows = db.execute("SELECT * FROM users WHERE id = :user_id",
                          user_id = session["user_id"])

        # Ensure that the password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("current")):
            return apology("invalid password", 403)
        
        # If password is correct change password
        else:
            db.execute("UPDATE users SET hash = :hash WHERE id = :user_id", 
                        hash = generate_password_hash(request.form.get("password")), 
                        user_id = session["user_id"])

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("change_password.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Query the database for owned stocks
    owned_stocks = db.execute("SELECT DISTINCT symbol FROM stocks WHERE user_id = :user_id", 
                               user_id = session["user_id"])

    # Query the database for user's cash
    user_cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])
    user_cash = user_cash[0]["cash"]
    total_cash = 0

    # If the user submits a request
    if request.method == "POST":
        
        # Ensure that the user has entered a number
        if not request.form.get("shares"):
            return apology("you must enter the number of shares you wish to sell", 403)

        # Ensure that the user entered a non-zero and non-negative integer
        if int(request.form.get("shares")) < 1:
            return apology("you must enter a non-negative and non-zero integer", 403)

        # Selected stock
        symbol = request.form.get("symbol")

        # Query API for current price
        current_stock = lookup(symbol)
        price = {"symbol": symbol, "price": float(current_stock["price"])}
        
        # Query the database
        
        stock_to_sell = db.execute("SELECT * FROM stocks WHERE symbol = :symbol", symbol = symbol)

        if int(request.form.get("shares")) > stock_to_sell[0]["shares"]:
            return apology("you don't have enough shares", 403)

        # Solve for the shares left, total sale, user's cash(after transaction), and stocks total price(after transaction)
        shares_left = int(stock_to_sell[0]["shares"]) - int(request.form.get("shares"))
        shares_transacted = int(request.form.get("shares")) - (int(request.form.get("shares")) * 2)
        total_sale = float(request.form.get("shares")) * float(price["price"])
        total_cash = total_sale + user_cash
        total = float(shares_left * price["price"])
        

        # Update the user's cash
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash = total_cash, user_id = session["user_id"])

        # Update history database
        db.execute("""INSERT INTO history (user_id, symbol, shares, price, date_time) 
                    VALUES (:user_id, :symbol, :shares, :price, :date_time)""", 
                    user_id = session["user_id"], symbol = symbol, shares = shares_transacted, price = price["price"], date_time = datetime.now())

        if shares_left == 0:
            db.execute("DELETE FROM stocks WHERE (symbol = :symbol AND user_id = :user_id)", symbol = symbol, user_id = session["user_id"])
        else:
            db.execute("""UPDATE stocks SET shares = :shares_left, total = :total 
                        WHERE (symbol = :symbol AND user_id = :user_id)""", 
                        shares_left = shares_left, total = total, symbol = symbol, user_id = session["user_id"])

        return redirect("/")

    else:
        return render_template("sell.html", owned_stocks = owned_stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
