<script setup lang="ts">
    const bindings: Record<string, string> = {
        'ShiftLeft': 'clockLeft',
        'ShiftRight': 'clockRight',
        'KeyZ': 'zerkLeft',
        'Slash': 'zerkRight',
    }

    const emit = defineEmits(['button'])

    onMounted(() => {
        console.log('KeyBinding.vue mounted')

        window.addEventListener('keydown', (e) => {
            const binding = bindings[e.code]
            if (binding) {
                console.log('binding', binding)
                emit('button', binding)
            }
        })
    })
</script>

<template>
    <div>keybinding template here</div>
</template>
