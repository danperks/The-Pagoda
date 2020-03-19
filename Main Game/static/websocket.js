const $log = $('#log');
const $msg = $('#msg');
const $submit = $('#submitMessage');


socket.onmessage = (e) => {
    const message = JSON.parse(e.data);
    switch (message.type) {
        case 'chat':
            $log.val(`${message.body}\n` + $log.val());
            break;
        default:
            console.error('Unknown message type');
    }
};
$submit.submit(event => {
    event.preventDefault();
    socket.send(createMessage(id, 'chat', $msg.val()));
    $msg.val('');
});