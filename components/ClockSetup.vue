<script setup lang="ts">
const initialSeconds = ref(600)
const incrementSeconds = ref(0)
</script>

<template>
    <div class="text-center text-[14vw]">
        {{ initialSeconds / 60 }}+{{ incrementSeconds }}
    </div>
</template>
