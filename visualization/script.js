function confirmSelection(nextPage) {
    window.location.href = nextPage;
}

function navigateToPage(page) {
    window.location.href = page;
}

function toggleItem(itemId, itemName) {
    const selectedItemsContainer = document.getElementById('selected-items-container');
    const itemCheckbox = document.getElementById(itemId);

    if (itemCheckbox.checked) {
        const newItem = document.createElement('div');
        newItem.className = 'item';
        newItem.id = `selected-${itemId}`;
        newItem.innerHTML = `
            <input type="checkbox" checked disabled>
            <label>${itemName}</label>
        `;
        selectedItemsContainer.appendChild(newItem);
    } else {
        const itemToRemove = document.getElementById(`selected-${itemId}`);
        if (itemToRemove) {
            selectedItemsContainer.removeChild(itemToRemove);
        }
    }
}

function toggleBag(bagId, bagName, bagSize) {
    const selectedBagList = document.getElementById('selected-bag-list');
    const bagCheckbox = document.getElementById(bagId);

    if (bagCheckbox.checked) {
        const newBagItem = document.createElement('div');
        newBagItem.className = 'item';
        newBagItem.id = `selected-${bagId}`;
        newBagItem.innerHTML = `
            <input type="checkbox" checked disabled>
            <label>${bagName}</label>
            <span>${bagSize}</span>
        `;
        selectedBagList.appendChild(newBagItem);
    } else {
        const itemToRemove = document.getElementById(`selected-${bagId}`);
        if (itemToRemove) {
            selectedBagList.removeChild(itemToRemove);
        }
    }
}

function addNewBag() {
    document.getElementById('bag-modal').style.display = 'flex';
}

function closeModal() {
    document.getElementById('bag-modal').style.display = 'none';
}

function saveNewBag() {
    const bagName = document.getElementById('bag-name').value.trim();
    const bagWidth = document.getElementById('bag-width').value.trim();
    const bagLength = document.getElementById('bag-length').value.trim();
    const bagHeight = document.getElementById('bag-height').value.trim();

    // 입력 값 검증
    if (bagName === '' || bagWidth === '' || bagLength === '' || bagHeight === '') {
        alert('가방 이름과 모든 사이즈를 입력해주세요.');
        return;
    }

    // 가방 크기 문자열 생성 (예: 30 * 15 * 45)
    const bagSize = `${bagWidth} * ${bagLength} * ${bagHeight}`;

    const newBagId = `bag${document.querySelectorAll('.item-list .item').length + 1}`;
    const newItem = document.createElement('div');
    newItem.className = 'item';
    newItem.innerHTML = `
        <input type="checkbox" id="${newBagId}" onchange="toggleBag('${newBagId}', '${bagName}', '${bagSize}')">
        <label for="${newBagId}">${bagName}</label>
        <span>${bagSize}</span>
    `;
    document.getElementById('bag-list').appendChild(newItem);

    closeModal();
    document.getElementById('bag-name').value = '';
    document.getElementById('bag-width').value = '';
    document.getElementById('bag-length').value = '';
    document.getElementById('bag-height').value = '';
}

// 각 숫자에 대한 색상 정의 (1: 빨강, 2: 파랑, 3: 초록 등)
const colors = {
    1: 'red',   // Red
    2: 'blue',  // Blue
    3: 'green', // Green
    0: 'white'  // White (for empty cells)
};

// 3차원 배열 정의
const threeDimensionalArray = [
    [   // 1층
        [0, 0, 0, 1, 1], 
        [2, 2, 0, 1, 1], 
        [2, 2, 0, 1, 1]
    ],
    [   // 2층
        [0, 0, 0, 1, 1], 
        [2, 2, 0, 1, 1], 
        [2, 2, 0, 1, 1]
    ],
    [   // 3층
        [3, 3, 0, 1, 1], 
        [3, 3, 0, 1, 1], 
        [3, 3, 0, 1, 1]
    ]
];

const canvas = document.getElementById('canvas2D');
const ctx = canvas.getContext('2d');

// 각 셀의 크기 설정
const cellWidth = 50;
const cellHeight = 50;

// 층(layer) 인덱스 초기화
let currentLayerIndex = 0;

// 2D 배열 렌더링 함수
function draw2DArray(layerIndex) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // 현재 층을 가져오기
    const layer = threeDimensionalArray[layerIndex];

    // 2D 배열을 캔버스에 그리기
    layer.forEach((row, rowIndex) => {
        row.forEach((cell, colIndex) => {
            // 각 셀의 좌표 계산
            const x = colIndex * cellWidth;
            const y = rowIndex * cellHeight;

            // 셀 색상 설정
            ctx.fillStyle = colors[cell] || 'white';

            // 사각형(셀) 그리기
            ctx.fillRect(x, y, cellWidth, cellHeight);

            // 셀 테두리 그리기
            ctx.strokeStyle = 'black';
            ctx.strokeRect(x, y, cellWidth, cellHeight);
        });
    });
}

// 슬라이더 이벤트 리스너
const layerSlider = document.getElementById('layerSlider');
layerSlider.addEventListener('input', () => {
    currentLayerIndex = parseInt(layerSlider.value, 10);
    draw2DArray(currentLayerIndex);
});

// 초기 층을 렌더링
draw2DArray(currentLayerIndex);