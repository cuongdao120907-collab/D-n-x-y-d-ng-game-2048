const size = 4;
let board = [];

function initBoard() {
    board = [];
    for (let i = 0; i < size; i++) {
        board.push([0, 0, 0, 0]);
    }
    addNumber();
    addNumber();
    drawBoard();
}

function addNumber() {
    let empty = [];
    for (let i = 0; i < size; i++)
        for (let j = 0; j < size; j++)
            if (board[i][j] === 0) empty.push({ i, j });

    if (empty.length === 0) return;

    const { i, j } = empty[Math.floor(Math.random() * empty.length)];
    board[i][j] = Math.random() < 0.9 ? 2 : 4;
}

function drawBoard() {
    const grid = document.getElementById("grid");
    grid.innerHTML = "";

    for (let i = 0; i < size; i++) {
        for (let j = 0; j < size; j++) {

            const cell = document.createElement("div");
            cell.className = "cell value-" + board[i][j];
            cell.textContent = board[i][j] === 0 ? "" : board[i][j];

            grid.appendChild(cell);
        }
    }
}

function compress(row) {
    let arr = row.filter(v => v !== 0);
    while (arr.length < size) arr.push(0);
    return arr;
}

function merge(row) {
    for (let i = 0; i < size - 1; i++) {
        if (row[i] !== 0 && row[i] === row[i + 1]) {
            row[i] *= 2;
            row[i + 1] = 0;
        }
    }
    return row;
}

function operate(row) {
    row = compress(row);
    row = merge(row);
    row = compress(row);
    return row;
}

function rotateLeft(matrix) {
    let res = [];
    for (let i = 0; i < size; i++) {
        res[i] = [];
        for (let j = 0; j < size; j++) {
            res[i][j] = matrix[j][size - i - 1];
        }
    }
    return res;
}

function move(dir) {
    let old = JSON.parse(JSON.stringify(board));

    if (dir === "left") {
        for (let i = 0; i < size; i++)
            board[i] = operate(board[i]);
    }

    if (dir === "right") {
        for (let i = 0; i < size; i++)
            board[i] = operate(board[i].reverse()).reverse();
    }

    if (dir === "up") {
        board = rotateLeft(board);
        for (let i = 0; i < size; i++)
            board[i] = operate(board[i]);
        board = rotateLeft(board);
        board = rotateLeft(board);
        board = rotateLeft(board);
    }

    if (dir === "down") {
        board = rotateLeft(board);
        for (let i = 0; i < size; i++)
            board[i] = operate(board[i].reverse()).reverse();
        board = rotateLeft(board);
        board = rotateLeft(board);
        board = rotateLeft(board);
    }

    if (JSON.stringify(old) !== JSON.stringify(board)) {
        addNumber();
    }

    drawBoard();
}

document.addEventListener("keydown", e => {
    if (e.key === "ArrowLeft") move("left");
    if (e.key === "ArrowRight") move("right");
    if (e.key === "ArrowUp") move("up");
    if (e.key === "ArrowDown") move("down");
});

window.onload = initBoard;
