const Koa = require('koa');
const cors = require('@koa/cors');
const bodyParser = require('koa-bodyparser');
const dotenv = require('dotenv');

dotenv.config();
const app = new Koa();

app.use(cors())
app.use(bodyParser());

const PORT = process.env.PORT || '3000';

// routes

const server = app.listen(PORT, () =>
    console.log(`Server is listening on port http://localhost:${PORT}.`),
);

app.use(async (ctx) => (ctx.body = { msg: `Welcome to this API.` }));

module.exports = { server }