<script setup lang="ts">
type ButtonAction = 'clockLeft' | 'clockRight' | 'zerkLeft' | 'zerkRight'

const bindings: Record<string, ButtonAction> = {
    ShiftLeft: 'clockLeft',
    ShiftRight: 'clockRight',
    KeyZ: 'zerkLeft',
    Slash: 'zerkRight',
}

window.addEventListener('keydown', (e) => {
    const binding = bindings[e.code]
    if (binding) {
        console.log('binding:', binding)
    }
})
</script>

<template>
    <div>
        <ClockSetup />

        <Clock ref="clockLeft" />
        <br>
        <Clock ref="clockRight" />
    </div>
</template>
