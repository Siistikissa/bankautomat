var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

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

app.use('/transactions', transactionsRouter);
app.use('/customers', customersRouter);
app.use('/cards', cardsRouter);
app.use('/accounts', accountsRouter);


module.exports = app;