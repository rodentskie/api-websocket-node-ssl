const Koa = require('koa');
const cors = require('@koa/cors');
const bodyParser = require('koa-bodyparser');
const dotenv = require('dotenv');

dotenv.config();
const app = new Koa();

app.use(cors());
app.use(bodyParser());

const PORT = process.env.PORT || '3000';

const server = app.listen(PORT, () =>
  console.log(`Server is listening on port http://localhost:${PORT}.`),
);
const io = require('socket.io')(server);

app.use(async (ctx) => (ctx.body = { msg: `Welcome to this API zzz.` }));

io.on('connection', (socket) => {
  console.log(
    `\nA socket has been connected: \nID: ${socket.id} \nOrigin: ${socket.handshake.headers.origin}`,
  );

  io.emit('congrats', {
    msg: 'Successfully connected!',
  });

  socket.on('ok', (data) => {
    console.log('Received:', data);
  });
});

module.exports = { app, io };
