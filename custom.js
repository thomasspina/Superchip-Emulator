function parseRomOptions(optionText) {
    try {
        return JSON.parse(optionText);
    } catch (error) {
        console.error("Failed to parse ROM options:", error);
        return null;
    }
}

function loadROM(optionText) {
    const romOptions = parseRomOptions(optionText);
    if (romOptions) {
        Module.ccall("loadROM", null, ["string"], [romOptions["game"]]);
    }
}

function applyInversion(optionText) {
    const romOptions = parseRomOptions(optionText);
    if (romOptions) {
        Module.ccall("invert", null, ["string"], [romOptions["game"]]);
    }
}

function toggleTheme() {
    const body = document.body;
    body.classList.toggle("light-mode");

    document.querySelectorAll("#rom-select, #rom-load").forEach((el) => {
        el.classList.toggle("dark-mode");
    });
}


// Initialize WebAssembly Module
Module["onRuntimeInitialized"] = function () {
    const romSelect = document.querySelector("#rom-select");
    const romLoad = document.querySelector("#rom-load");
    const invertButton = document.querySelector("#invert");

    loadROM(romSelect.value);

    romLoad.addEventListener("click", () => {
        loadROM(romSelect.value);
    });

    invertButton.addEventListener("click", () => {
        toggleTheme();

        const changeIcon = (icon) => {
            icon.classList.toggle("fa-solid");
        }

        applyInversion(romSelect.value);
    });
};

document.querySelector("#open-info").addEventListener("click", () => {
    document.querySelector("#info-dialogue").showModal();
});

document.querySelector("#close-info").addEventListener("click", () => {
    document.querySelector("#info-dialogue").close();
});
