var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');


const loginRouter = require('./routes/login');
const transactionsRouter = require('./routes/transactions');
const customersRouter = require('./routes/customers');
const cardsRouter = require('./routes/cards');
const accountsRouter = require('./routes/accounts');


var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use('/login', loginRouter);
app.use(authenticateToken);
app.use('/transactions', transactionsRouter);
app.use('/customers', customersRouter);
app.use('/cards', cardsRouter);
app.use('/accounts', accountsRouter);

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, function(err, user) {
  
      if (err) return res.sendStatus(403)

      req.user = user
  
      next()
    })
  }

module.exports = app;